#include "stdafx.h"
#include "SkinModelData.h"
#include "Animation.h"
//#define _CRT_SECURE_NO_WARNINGS

// Delete関連。
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

UINT                        g_NumBoneMatricesMax = 0;
D3DXMATRIXA16*              g_pBoneMatrices = NULL;

namespace {
	//--------------------------------------------------------------------------------------
	// フレーム階層の結合されたトランスフォーム行列を更新
	//--------------------------------------------------------------------------------------
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, const D3DXMATRIX* pParentMatrix)
	{
		D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;

		// フレームにある行列からワールド変換行列を生成。
		if (pParentMatrix != NULL)
			D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix,
			&pFrame->TransformationMatrix,
			pParentMatrix);
		else
			pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
		//兄弟フレームの行列をワールド変換行列に。
		if (pFrame->pFrameSibling != NULL)
		{
			UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
		}
		//子フレームをの行列をワールド変換行列に。
		if (pFrame->pFrameFirstChild != NULL)
		{
			UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
		}
	}

	void InnerDestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
	{
		UINT iMaterial;
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

		SAFE_DELETE_ARRAY(pMeshContainer->pAttributeTable);
		SAFE_DELETE_ARRAY(pMeshContainer->Name);
		SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
		SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
		SAFE_DELETE_ARRAY(pMeshContainer->pBoneOffsetMatrices);

		// release all the allocated textures
		if (pMeshContainer->ppTextures != NULL)
		{
			for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
			{
				SAFE_RELEASE(pMeshContainer->ppTextures[iMaterial]);
			}
		}

		SAFE_DELETE_ARRAY(pMeshContainer->ppTextures);
		SAFE_DELETE_ARRAY(pMeshContainer->ppBoneMatrixPtrs);
		SAFE_RELEASE(pMeshContainer->pBoneCombinationBuf);
		SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
		SAFE_RELEASE(pMeshContainer->pSkinInfo);
		SAFE_RELEASE(pMeshContainer->pOrigMesh);
		SAFE_DELETE(pMeshContainer);
	}

	//アニメーションおよびレンダリングのためのメッシュ階層をセットアップ。
	HRESULT GenerateSkinnedMesh(
		IDirect3DDevice9* pd3dDevice,
		D3DXMESHCONTAINER_DERIVED* pMeshContainer
		)
	{
		HRESULT hr = S_OK;
		D3DCAPS9 d3dCaps;
		pd3dDevice->GetDeviceCaps(&d3dCaps);

		if (pMeshContainer->pSkinInfo == NULL)
			return hr;
		SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
		SAFE_RELEASE(pMeshContainer->pBoneCombinationBuf);

		{
			// Get palette size
			// First 9 constants are used for other data.  Each 4x3 matrix takes up 3 constants.
			// (96 - 9) /3 i.e. Maximum constant count - used constants 
			UINT MaxMatrices = 26;
			pMeshContainer->NumPaletteEntries = min(MaxMatrices, pMeshContainer->pSkinInfo->GetNumBones());

			DWORD Flags = D3DXMESHOPT_VERTEXCACHE;
			if (d3dCaps.VertexShaderVersion >= D3DVS_VERSION(1, 1))
			{
				pMeshContainer->UseSoftwareVP = false;
				Flags |= D3DXMESH_MANAGED;
			}
			else
			{
				pMeshContainer->UseSoftwareVP = true;
				Flags |= D3DXMESH_SYSTEMMEM;
			}

			SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
			hr = pMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh
				(
				pMeshContainer->pOrigMesh,
				Flags,
				pMeshContainer->NumPaletteEntries,
				pMeshContainer->pAdjacency,
				NULL, NULL, NULL,
				&pMeshContainer->NumInfl,
				&pMeshContainer->NumAttributeGroups,
				&pMeshContainer->pBoneCombinationBuf,
				&pMeshContainer->MeshData.pMesh);
			if (FAILED(hr))
				goto e_Exit;



			// FVF has to match our declarator. Vertex shaders are not as forgiving as FF pipeline
			DWORD NewFVF = (pMeshContainer->MeshData.pMesh->GetFVF() & D3DFVF_POSITION_MASK) | D3DFVF_NORMAL |
				D3DFVF_TEX1 | D3DFVF_LASTBETA_UBYTE4;
			if (NewFVF != pMeshContainer->MeshData.pMesh->GetFVF())
			{
				LPD3DXMESH pMesh;
				//CloneMeshFVF(メッシュの作成オプションを指定。
				//出力メッシュに含まれる頂点の頂点フォーマットを指定。
				//メッシュに関連付けられているデバイス オブジェクト。
				//コピーされたメッシュ,)柔軟な頂点フォーマット (FVF) コードを使ってメッシュのコピーを作成する。
				//戻り値は成功した場合は、D3D_OK。
				hr = pMeshContainer->MeshData.pMesh->CloneMeshFVF(pMeshContainer->MeshData.pMesh->GetOptions(), NewFVF,
					pd3dDevice, &pMesh);
				if (!FAILED(hr))
				{
					pMeshContainer->MeshData.pMesh->Release();
					pMeshContainer->MeshData.pMesh = pMesh;
					pMesh = NULL;
				}
			}

			D3DVERTEXELEMENT9 pDecl[MAX_FVF_DECL_SIZE];
			LPD3DVERTEXELEMENT9 pDeclCur;
			hr = pMeshContainer->MeshData.pMesh->GetDeclaration(pDecl);
			if (FAILED(hr))
				goto e_Exit;

			// the vertex shader is expecting to interpret the UBYTE4 as a D3DCOLOR, so update the type 
			//   NOTE: this cannot be done with CloneMesh, that would convert the UBYTE4 data to float and then to D3DCOLOR
			//          this is more of a "cast" operation
			pDeclCur = pDecl;
			while (pDeclCur->Stream != 0xff)
			{
				if ((pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES) && (pDeclCur->UsageIndex == 0))
					pDeclCur->Type = D3DDECLTYPE_D3DCOLOR;
				pDeclCur++;
			}

			hr = pMeshContainer->MeshData.pMesh->UpdateSemantics(pDecl);
			if (FAILED(hr))
				goto e_Exit;

			// allocate a buffer for bone matrices, but only if another mesh has not allocated one of the same size or larger
			if (g_NumBoneMatricesMax < pMeshContainer->pSkinInfo->GetNumBones())
			{
				g_NumBoneMatricesMax = pMeshContainer->pSkinInfo->GetNumBones();

				// Allocate space for blend matrices
				delete[] g_pBoneMatrices;
				g_pBoneMatrices = new D3DXMATRIXA16[g_NumBoneMatricesMax];
				if (g_pBoneMatrices == NULL)
				{
					hr = E_OUTOFMEMORY;
					goto e_Exit;
				}
			}

		}
	e_Exit:
		return hr;
	}
	HRESULT AllocateName(LPCSTR Name, LPSTR* pNewName)
	{
		UINT cbLength;

		if (Name != NULL)
		{
			cbLength = (UINT)strlen(Name) + 1;
			*pNewName = new CHAR[cbLength];
			if (*pNewName == NULL)
				return E_OUTOFMEMORY;
			memcpy(*pNewName, Name, cbLength * sizeof(CHAR));
		}
		else
		{
			*pNewName = NULL;
		}

		return S_OK;
	}
	//--------------------------------------------------------------------------------------
	// Called to setup the pointers for a given bone to its transformation matrix
	//関数内部でルートフレームから子フレームを検索しながら、メッシュ情報を持つフレームを探し当て、そこに格納されている「ボーン」の情報を格納している。
	//--------------------------------------------------------------------------------------
	HRESULT SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME rootFrame)
	{
		UINT iBone, cBones;
		D3DXFRAME_DERIVED* pFrame;

		//MeshContainerはメッシュに含まれるボーンなどの色々な情報を格納している。
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

		// if there is a skinmesh, then setup the bone matrices
		//アニメーションするかしないかの判定。
		if (pMeshContainer->pSkinInfo != NULL)
		{
			cBones = pMeshContainer->pSkinInfo->GetNumBones();

			pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[cBones];
			if (pMeshContainer->ppBoneMatrixPtrs == NULL)
				return E_OUTOFMEMORY;

			for (iBone = 0; iBone < cBones; iBone++)
			{
				pMeshContainer->ppBoneMatrixPtrs[iBone] = NULL;
				LPCSTR boneName = pMeshContainer->pSkinInfo->GetBoneName(iBone);
				//メッシュがどのボーンを使うかをD3DXFrameFind(子フレームが見つかった場合はそれを返す)を使って探して設定している。
				pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(rootFrame,
					boneName);
				if (pFrame == NULL)
					return E_FAIL;

				pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformationMatrix;
			}
		}
		pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(rootFrame, "_face");
		return S_OK;
	}


	//--------------------------------------------------------------------------------------
	// Called to setup the pointers for a given bone to its transformation matrix
	//ループによってフレームに格納されているメッシュコンテナを格納。
	//--------------------------------------------------------------------------------------
	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME pFrame, LPD3DXFRAME pRootFrame)
	{
		HRESULT hr;

		//親フレーム。
		if (pFrame->pMeshContainer != NULL)
		{
			hr = SetupBoneMatrixPointersOnMesh(pFrame->pMeshContainer, pRootFrame);
			if (FAILED(hr))
				return hr;
		}

		//兄弟フレーム。
		if (pFrame->pFrameSibling != NULL)
		{
			hr = SetupBoneMatrixPointers(pFrame->pFrameSibling, pRootFrame);
			if (FAILED(hr))
				return hr;
		}

		//子フレーム。
		if (pFrame->pFrameFirstChild != NULL)
		{
			hr = SetupBoneMatrixPointers(pFrame->pFrameFirstChild, pRootFrame);
			if (FAILED(hr))
				return hr;
		}

		return S_OK;
	}
	//ID3DXAllocateHierarchyはユーザの実装が必要。
	//インターフェイスは実体を持たない抽象クラス、抽象クラスを。
	//ID3DXAllocateHierarchy AlllocHrcy。
	//と実体を宣言すると、コンパイラから抽象オブジェクトは実体化できないと怒られる。
	//しかし。
	//ID3DXAllocateHierarchy *pAlllocHrcy。
	//とポインタ宣言することは可能（ポインタは実体ではないから）しかし。
	//これをD3DXLoadMeshHierarchyFromX関数に渡す暴挙に出ると、関数内部でポインタが参照された瞬間メモリ保護違反でアプリケーションが止まる、つまり。
	//ID3DXAllocateHierarchyからクラスを派生して、定義されている仮想関数を実際に実装する必要がある。
	//ID3DXAllocateHierarchyはオブジェクトの作成と削除を担当する専門家。
	class AllocateHierarchy : public ID3DXAllocateHierarchy
	{
	public:
		//こう書かないとエラーになる。
		STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
		STDMETHOD(CreateMeshContainer)(THIS_
			LPCSTR Name,
			CONST D3DXMESHDATA *pMeshData,
			CONST D3DXMATERIAL *pMaterials,
			CONST D3DXEFFECTINSTANCE *pEffectInstances,
			DWORD NumMaterials,
			CONST DWORD *pAdjacency,
			LPD3DXSKININFO pSkinInfo,
			LPD3DXMESHCONTAINER *ppNewMeshContainer);
		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);

		AllocateHierarchy()
		{
		}
	};
	//--------------------------------------------------------------------------------------
	// Name: AllocateHierarchy::CreateFrame(ボーンのツリー階層を作っている(親から子、子から孫みたいに))。
	// Desc: 
	//--------------------------------------------------------------------------------------
	HRESULT AllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME* ppNewFrame)
	{
		HRESULT hr = S_OK;
		D3DXFRAME_DERIVED* pFrame;

		*ppNewFrame = NULL;

		pFrame = new D3DXFRAME_DERIVED;
		if (pFrame == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}

		hr = AllocateName(Name, &pFrame->Name);
		if (FAILED(hr))
			goto e_Exit;

		// initialize other data members of the frame
		//ボーンのと合成行列の初期化。
		D3DXMatrixIdentity(&pFrame->TransformationMatrix);
		D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);

		//次に子と孫のフレームの初期化。
		pFrame->pMeshContainer = NULL;
		pFrame->pFrameSibling = NULL;
		pFrame->pFrameFirstChild = NULL;

		*ppNewFrame = pFrame;
		pFrame = NULL;

	e_Exit:
		delete pFrame;
		return hr;
	}
	//--------------------------------------------------------------------------------------
	// Name: AllocateHierarchy::CreateMeshContainer()
	//メッシュコンテナ(D3DXMESHCONTAINER構造体)を作成。
	// Desc: 
	//--------------------------------------------------------------------------------------
	HRESULT AllocateHierarchy::CreateMeshContainer(
		LPCSTR Name,									//メッシュの名前。
		CONST D3DXMESHDATA *pMeshData,					//メッシュ データ構造体へのポインター。
		CONST D3DXMATERIAL *pMaterials,					//メッシュに使用するマテリアルの配列。
		CONST D3DXEFFECTINSTANCE *pEffectInstances,		//メッシュに使用するエフェクト インスタンスの配列。
		DWORD NumMaterials,								//マテリアル配列内のマテリアル数。
		CONST DWORD *pAdjacency,						//メッシュの隣接ポリゴンインデックスの配列。
		LPD3DXSKININFO pSkinInfo,						//スキンデータが見つかった場合のスキンメッシュオブジェクトへのポインター。
		LPD3DXMESHCONTAINER *ppNewMeshContainer)		//作成されたメッシュコンテナーを返す。
	{
		HRESULT hr;
		D3DXMESHCONTAINER_DERIVED *pMeshContainer = NULL;
		UINT NumFaces;
		UINT iMaterial;
		UINT iBone, cBones;
		LPDIRECT3DDEVICE9 pd3dDevice = NULL;

		LPD3DXMESH pMesh = NULL;

		*ppNewMeshContainer = NULL;

		// this sample does not handle patch meshes, so fail when one is found
		//通常メッシュかどうか。
		if (pMeshData->Type != D3DXMESHTYPE_MESH)
		{
			hr = E_FAIL;
			goto e_Exit;
		}

		// get the pMesh interface pointer out of the mesh data structure
		pMesh = pMeshData->pMesh;
		DWORD numVert = pMesh->GetNumVertices();
		// this sample does not FVF compatible meshes, so fail when one is found
		//メッシュに何一つ情報が入っていない場合のエラー。
		if (pMesh->GetFVF() == 0)
		{
			hr = E_FAIL;
			goto e_Exit;
		}

		// allocate the overloaded structure to return as a D3DXMESHCONTAINER
		// メッシュコンテナオブジェクトの生成。
		pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
		if (pMeshContainer == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}
		memset(pMeshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

		// make sure and copy the name.  All memory as input belongs to caller, interfaces can be addref'd though
		//メモリを確保して文字列を格納する ( フレーム等の名前格納用 )。
		hr = AllocateName(Name, &pMeshContainer->Name);
		//// メモリ確保失敗。
		if (FAILED(hr))
			goto e_Exit;

		pMesh->GetDevice(&pd3dDevice);
		//メッシュに含まれるポリゴンの数を取得します。
		NumFaces = pMesh->GetNumFaces();

		pMeshContainer->MeshData.pMesh = pMesh;
		//メッシュコンテナに通常メッシュを設定。
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		//参照カウンタを1つ増やす必要がある。
		//同じテクスチャなどインスタンスが何個使っているかを管理している。
		//減算はインスタンスのデストラクタが呼ばれた時に行われる。
		pMesh->AddRef();

		D3DVERTEXELEMENT9 decl[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
			{ 0, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
			{ 0, 48, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
			{ 0, 60, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
			{ 0, 72, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};


		// allocate memory to contain the material information.  This sample uses
		//   the D3D9 materials and texture names instead of the EffectInstance style materials
		pMeshContainer->NumMaterials = max(1, NumMaterials);
		pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
		pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
		pMeshContainer->textureName.resize(pMeshContainer->NumMaterials);
		//はある1つの三角ポリゴンに隣接する3つのポリゴンインデックス番号を格納した隣接ポリゴンインデックス。
		pMeshContainer->pAdjacency = new DWORD[NumFaces * 3];
		if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}

		// 隣接情報をコピー。
		memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD)* NumFaces * 3);
		memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9)* pMeshContainer->NumMaterials);

		// if materials provided, copy them
		// 受け取ったマテリアルをコピーする。
		if (NumMaterials > 0)
		{
			// まずは丸ごとコピー。
			memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL)* NumMaterials);

			//// テクスチャ名を保存する。
			for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
			{
				if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
				{
					char* baseDir = "image/";
					char filePath[64];
					strcpy(filePath, baseDir);
					strcat(filePath, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
					//ファイルを基にしてテクスチャを作成する。
					if (FAILED(D3DXCreateTextureFromFile(
						pd3dDevice,
						filePath,//ファイル名を指定する文字列へのポインタ。コンパイラの設定がUnicodeを要求している場合、データタイプLPCTSTRはLPCWSTRになる。それ以外の場合は、この文字列のデータタイプはLPCSTR 。
						&pMeshContainer->ppTextures[iMaterial]))//作成されたキューブ テクスチャ オブジェクトを表す、IDirect3DTexture9 インターフェイスへのポインタのアドレス。
						) {
						pMeshContainer->ppTextures[iMaterial] = NULL;
					}
					pMeshContainer->textureName[iMaterial] = pMeshContainer->pMaterials[iMaterial].pTextureFilename;

					// don't remember a pointer into the dynamic memory, just forget the name after loading
					pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;

				}
			}
		}
		else // if no materials provided, use a default one
		{
			pMeshContainer->pMaterials[0].pTextureFilename = NULL;
			memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
			pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
			pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
			pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
			pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
		}

		pMeshContainer->pOrigMesh = pMesh;
		pMesh->AddRef();

		// if there is skinning information, save off the required data and then setup for HW skinning
		if (pSkinInfo != NULL)
		{
			// first save off the SkinInfo and original mesh data
			//スキン情報を格納。
			pMeshContainer->pSkinInfo = pSkinInfo;
			pSkinInfo->AddRef();

			

			// Will need an array of offset matrices to move the vertices from the figure space to the bone's space
			// 物体のローカル空間からボーン空間に頂点を移動するためのオフセット行列用の配列を用意する。
			cBones = pSkinInfo->GetNumBones();
			pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[cBones];
			if (pMeshContainer->pBoneOffsetMatrices == NULL)
			{
				hr = E_OUTOFMEMORY;
				goto e_Exit;
			}

			// get each of the bone offset matrices so that we don't need to get them later
			// それぞれのボーンのオフセット行列(ボーンの逆行列)を取り出して保存する。
			//自分を原点にボーンが移動、回転させるようにするから正しい移動量で動く。
			for (iBone = 0; iBone < cBones; iBone++)
			{
				pMeshContainer->pBoneOffsetMatrices[iBone] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
			}

			// GenerateSkinnedMesh will take the general skinning information and transform it to a HW friendly version
			// スキンメッシュを作成する。
			hr = GenerateSkinnedMesh(pd3dDevice, pMeshContainer);
			if (FAILED(hr))
				goto e_Exit;

			LPD3DXMESH pOutMesh;
			hr = pMeshContainer->MeshData.pMesh->CloneMesh(
				pMeshContainer->MeshData.pMesh->GetOptions(),
				decl,
				pd3dDevice, &pOutMesh);
			if (FAILED(hr))
				goto e_Exit;
			//D3DXComputeNormals(pOutMesh, NULL);
			//D3DXComputeTangentFrameExはメッシュの接線フレームの計算を実行し、接線ベクトル(ポリゴンの向きに直行するベクトル)、従法線ベクトル(ポリゴンの向きとポリゴンの向きに直行するベクトルに直行するベクトル)、および必要に応じて法線ベクトル(ポリゴンの向き)が生成される。
			hr = D3DXComputeTangentFrameEx(
				pOutMesh,				// ID3DXMeshメッシュオブジェクトへのポインタ。
				D3DDECLUSAGE_TEXCOORD,	//テクスチャー座標の入力セマンティクスを指定する、D3DX_DEFAULTを指定するとこの関数はテクスチャー座標をないものと見なし、法線ベクトル計算が指定されない限り関数は失敗する。
				0,						//メッシュに複数のテクスチャー座標がある場合に、接線フレームの計算に使用するテクスチャー座標を指定する。0 の場合、メッシュにはテクスチャー座標が1つしかない。
				D3DDECLUSAGE_TANGENT,	//出力セマンティクス(セマンティクス(意味)、この情報は何なのかと言う情報を付与している、TANGENTなら接線)のタイプを指定する。通常、Uテクスチャー座標を基準とする偏微分が格納されることを表すD3DDECLUSAGE_TANGENTを指定する。D3DX_DEFAULTの場合、この偏微分は格納されない。
				0,						//U テクスチャー座標を基準とする偏微分を格納するセマンティクス インデックスを指定する。
				D3DX_DEFAULT,			//D3DDECLUSAGE型を指定する。通常、V テクスチャー座標を基準とする偏微分が格納されることを表すD3DDECLUSAGE_BINORMALを指定する。D3DX_DEFAULTの場合、この偏微分は格納されない。
				0,						//Vテクスチャー座標を基準とする偏微分を格納するセマンティクスインデックスを指定する。
				D3DDECLUSAGE_NORMAL,	//出力標準セマンティクスを指定する。通常、頂点ごとの法線ベクトルが格納されることを表すD3DDECLUSAGE_NORMALを指定する。D3DX_DEFAULTの場合、この法線ベクトルは格納されない。
				0,						//頂点ごとの法線ベクトルを格納するセマンティクス インデックスを指定する。
				0,						//接線フレームの計算のオプションを指定する。
				NULL,					//面ごとの3つの WORD値を格納する配列へのポインター。
				0.01f,    //ボケ具合.値をおおきくするとぼけなくなる。
				0.25f,
				0.01f,
				&pOutMesh,	//算出された接線ベクトル、従法線ベクトル、および法線ベクトルのデータを受け取る出力ID3DXMeshメッシュオブジェクトへのポインターのアドレス。
				NULL		//このメソッドで計算した新しい頂点から元の頂点へのマッピングを受け取る出力ID3DXBufferバッファーオブジェクトへのポインターのアドレス、バッファーは DWORDの配列であり、配列のサイズはppMeshOutの頂点の数として定義される。
				);
			pMeshContainer->MeshData.pMesh->Release();
			pMeshContainer->MeshData.pMesh = pOutMesh;


			//std::vector<DWORD> adjList;
			//adjList.resize(3 * pOutMesh->GetNumFaces());
			////メッシュエッジのリストと、各エッジを共有する面のリストを生成する
			//pOutMesh->GenerateAdjacency(1.0f / 512.0f, &adjList[0]); // EPSIONは適当な値(1.0f/512とか)

			//DWORD numVert = pOutMesh->GetNumVertices();  // Optimizeの一種
			//pOutMesh->OptimizeInplace(D3DXMESHOPT_COMPACT, &adjList[0], NULL, NULL, NULL);
			//numVert = pOutMesh->GetNumVertices();
			//↑のコメントアウトされているプログラムを使うとメモリーリークを引き起す

			if (FAILED(hr))
				goto e_Exit;
		}
		else {
			LPD3DXMESH pOutMesh;
			DWORD numVert = pMeshContainer->MeshData.pMesh->GetNumVertices();
			hr = pMeshContainer->MeshData.pMesh->CloneMesh(
				pMeshContainer->MeshData.pMesh->GetOptions(),
				decl,
				pd3dDevice, &pOutMesh);

			numVert = pMeshContainer->MeshData.pMesh->GetNumVertices();
			hr = D3DXComputeTangentFrameEx(
				pOutMesh,
				D3DDECLUSAGE_TEXCOORD,
				0,
				D3DDECLUSAGE_TANGENT,
				0,
				D3DX_DEFAULT,
				0,
				D3DDECLUSAGE_NORMAL,
				0,
				0,
				NULL,
				0.01f,    //ボケ具合.値をおおきくするとぼけなくなる。
				0.25f,
				0.01f,
				&pOutMesh,
				NULL
				);
			numVert = pOutMesh->GetNumVertices();
			pMeshContainer->MeshData.pMesh->Release();
			pMeshContainer->MeshData.pMesh = pOutMesh;
			if (FAILED(hr))
				goto e_Exit;
			//LPD3DXMESH optMesh;
			//std::vector<DWORD> adjList;
			////リストのサイズが要求されたサイズ (_Newsize) よりも小さい場合は、要求されたサイズになるまで、リストに要素が追加される 。 
			////リストのサイズが要求されたサイズよりも大きい場合は、リストのサイズが _Newsize になるまで、リストの末尾に近い要素から順に削除される。
			////リストの現在のサイズが要求されたサイズと同じ場合は、何も実行されない。
			//adjList.resize(3 * pOutMesh->GetNumFaces());
			////メッシュエッジのリスト(各エッジに繋がってるポリゴンの情報)と、各エッジを共有する面のリストを生成する。
			//pOutMesh->GenerateAdjacency(1.0f, &adjList[0]); // EPSIONは適当な値(1.0f/512とか)。
			//numVert = pOutMesh->GetNumVertices();  // Optimizeの一種。
			//pOutMesh->Optimize(D3DXMESHOPT_COMPACT, &adjList[0], NULL, NULL, NULL, &optMesh);
			//numVert = optMesh->GetNumVertices();

		}

		*ppNewMeshContainer = pMeshContainer;
		pMeshContainer = NULL;

	e_Exit:
		pd3dDevice->Release();

		// call Destroy function to properly clean up the memory allocated 
		if (pMeshContainer != NULL)
		{
			DestroyMeshContainer(pMeshContainer);
		}

		return hr;
	}
	//--------------------------------------------------------------------------------------
	// Name: AllocateHierarchy::DestroyFrame()
	// Desc: 
	//--------------------------------------------------------------------------------------
	HRESULT AllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
	{
		SAFE_DELETE_ARRAY(pFrameToFree->Name);	//char型の配列として動的にメモリを確保しているのでdeleteする必要がある。
		SAFE_DELETE(pFrameToFree);
		return S_OK;
	}




	//--------------------------------------------------------------------------------------
	// Name: AllocateHierarchy::DestroyMeshContainer()
	//沢山のメモリをちまちまと確保しているので、漏らすことなく消さないといけない。
	// Desc: 
	//--------------------------------------------------------------------------------------
	HRESULT AllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
	{
		InnerDestroyMeshContainer(pMeshContainerBase);
		return S_OK;
	}


}
SkinModelData::SkinModelData() :
m_isClone(false),
m_frameRoot(nullptr),
m_pAnimController(nullptr)
{
}
SkinModelData::~SkinModelData()
{
	Release();
}
void SkinModelData::Release()
{
	if (m_pAnimController) {
		m_pAnimController->Release();
	}
	if (m_isClone && m_frameRoot) {
		//クローン
		DeleteCloneSkeleton(m_frameRoot);
		m_frameRoot = nullptr;
	}
	else {
		//オリジナル。
		DeleteSkeleton(m_frameRoot);
	}
}

void SkinModelData::DeleteSkeleton(LPD3DXFRAME frame)
{
	if (!frame) {
		return;
	}
	if (frame->pMeshContainer != NULL)
	{
		//メッシュコンテナがある。
		InnerDestroyMeshContainer(frame->pMeshContainer);
	}

	if (frame->pFrameSibling != NULL)
	{
		//兄弟がいる。
		DeleteSkeleton(frame->pFrameSibling);
	}

	if (frame->pFrameFirstChild != NULL)
	{
		//子供がいる。
		DeleteSkeleton(frame->pFrameFirstChild);
	}
	SAFE_DELETE_ARRAY(frame->Name);
	SAFE_DELETE(frame);
}


void SkinModelData::SetupOutputAnimationRegist(LPD3DXFRAME frame, ID3DXAnimationController* animCtr)
{
	if (animCtr == nullptr) {
		return;
	}
	HRESULT hr = animCtr->RegisterAnimationOutput(frame->Name, &frame->TransformationMatrix, nullptr, nullptr, nullptr);
	if (frame->pFrameSibling != nullptr) {
		SetupOutputAnimationRegist(frame->pFrameSibling, animCtr);
	}
	if (frame->pFrameFirstChild != nullptr)
	{
		SetupOutputAnimationRegist(frame->pFrameFirstChild, animCtr);
	}
}

void SkinModelData::LoadModelData(const char* filePath, Animation* anim)
{
	AllocateHierarchy alloc;
	//xファイル内に定義されているポリゴンメッシュのフレーム階層を読み込んで格納する関数(xファイルからアニメーション情報を取り出す)。
	HRESULT hr = D3DXLoadMeshHierarchyFromX(
		filePath,	//xファイルのファイルパス。
		D3DXMESH_VB_MANAGED,	//メッシュ作成のオプション、D3DXMESH_MANAGEDを指定するのが一般的、Direct3Dが管理するメモリ下に作成。
		g_pd3dDevice,	//デバイスへのポインタ。
		&alloc,			//ID3DXAllocateHierarchyインターフェイスへのポインタ(指定xファイルからフレーム階層を構築)。
		nullptr,		//xファイル内にユーザ定義部分があるとき、その情報をここに格納。
		&m_frameRoot,	//D3DXFRAME構造体へのダブルポインタで、ここにフレーム階層の親分（ルートフレーム）へのポインタのポインタが返る、このポインタを通して子フレームにアクセスできる、要するにフレーム階層の全てが格納される。
		&m_pAnimController	//ID3DXAnimationControllerインターフェイスへのポインタで、xファイル内のアニメーションに対応するアニメーションコントローラへのポインタが返る。
		);
	if (FAILED(hr)) {
		return;
	}
	//m_m_pAnimController->(0);
	SetupBoneMatrixPointers(m_frameRoot, m_frameRoot);
	if (anim && m_pAnimController) {
		anim->Initialize(m_pAnimController);
	}
}

void SkinModelData::DeleteCloneSkeleton(LPD3DXFRAME frame)
{

	if (frame->pFrameSibling != nullptr) {
		//兄弟
		DeleteCloneSkeleton(frame->pFrameSibling);
	}
	if (frame->pFrameFirstChild != nullptr)
	{
		//子供。
		DeleteCloneSkeleton(frame->pFrameFirstChild);
	}
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)(frame->pMeshContainer);
	if (pMeshContainer) {
		SAFE_DELETE_ARRAY(pMeshContainer->ppBoneMatrixPtrs);
		SAFE_DELETE(pMeshContainer);
	}
	SAFE_DELETE_ARRAY(frame->Name);
	SAFE_DELETE(frame);
}

void SkinModelData::CloneSkeleton(LPD3DXFRAME& dstFrame, LPD3DXFRAME srcFrame)
{
	//名前と行列をコピー。
	dstFrame->TransformationMatrix = srcFrame->TransformationMatrix;
	//メッシュコンテナをコピー。メッシュは使いまわす。
	if (srcFrame->pMeshContainer) {
		dstFrame->pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
		((D3DXMESHCONTAINER_DERIVED*)dstFrame->pMeshContainer)->Clone(((D3DXMESHCONTAINER_DERIVED*)(srcFrame->pMeshContainer)));
		//memcpyをするとオリジナルのメッシュコンテナーのtextureNameが保持しているポインターとクローンしたメッシュコンテナーのtextureNameが保持しているポインターが
		//同じ所を指しているので複数回、削除を行うと一回目で削除された所を二回目でも削除しようとしてプログラムが落ちる。
		//なので新しくクローン関数を作ってオリジナルのtextureName分のメモリを新しく確保してクローンがその新しく作った方を指すようにして回避した。
		//新しくメモリを確保しているので重い。
		//memcpy(dstFrame->pMeshContainer, srcFrame->pMeshContainer, sizeof(D3DXMESHCONTAINER_DERIVED));
	}
	else {
		dstFrame->pMeshContainer = NULL;
	}
	AllocateName(srcFrame->Name, &dstFrame->Name);


	if (srcFrame->pFrameSibling != nullptr) {
		//兄弟がいるので、兄弟のためのメモリを確保。
		dstFrame->pFrameSibling = new D3DXFRAME_DERIVED;
		dstFrame->pFrameSibling->pFrameFirstChild = nullptr;
		dstFrame->pFrameSibling->pFrameSibling = nullptr;
		dstFrame->pFrameSibling->pMeshContainer = nullptr;
		CloneSkeleton(dstFrame->pFrameSibling, srcFrame->pFrameSibling);
	}
	if (srcFrame->pFrameFirstChild != nullptr)
	{
		//子供がいるので、子供のためのメモリを確保。
		dstFrame->pFrameFirstChild = new D3DXFRAME_DERIVED;
		dstFrame->pFrameFirstChild->pFrameFirstChild = nullptr;
		dstFrame->pFrameFirstChild->pFrameSibling = nullptr;
		dstFrame->pFrameFirstChild->pMeshContainer = nullptr;

		CloneSkeleton(dstFrame->pFrameFirstChild, srcFrame->pFrameFirstChild);
	}
}

void SkinModelData::CloneModelData(const SkinModelData& modelData, Animation* anim)
{
	//スケルトン(ボーンのひとかたまり)の複製を作成。。
	m_isClone = true;
	m_frameRoot = new D3DXFRAME_DERIVED;
	m_frameRoot->pFrameFirstChild = nullptr;
	m_frameRoot->pFrameSibling = nullptr;
	m_frameRoot->pMeshContainer = nullptr;
	CloneSkeleton(m_frameRoot, modelData.m_frameRoot);
	//アニメーションコントローラを作成して、スケルトンと関連付けを行う。
	if (modelData.m_pAnimController) {
		modelData.m_pAnimController->CloneAnimationController(
			modelData.m_pAnimController->GetMaxNumAnimationOutputs(),
			modelData.m_pAnimController->GetMaxNumAnimationSets(),
			modelData.m_pAnimController->GetMaxNumTracks(),
			modelData.m_pAnimController->GetMaxNumEvents(),
			&m_pAnimController
		);

		SetupOutputAnimationRegist(m_frameRoot, m_pAnimController);

		if (anim && m_pAnimController) {
			anim->Initialize(m_pAnimController);
		}
	}
	SetupBoneMatrixPointers(m_frameRoot, m_frameRoot);
}

void SkinModelData::UpdateBoneMatrix(const D3DXMATRIX& matWorld)
{
	UpdateFrameMatrices(m_frameRoot, &matWorld);
}

LPD3DXMESH SkinModelData::GetOrgMeshFirst()
{
	return GetOrgMesh(m_frameRoot);
}

LPD3DXMESH SkinModelData::GetOrgMesh(LPD3DXFRAME frame)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)(frame->pMeshContainer);
	if (pMeshContainer != NULL) {
		return pMeshContainer->pOrigMesh;
	}
	if (frame->pFrameSibling != NULL) {
		//兄弟
		LPD3DXMESH mesh = GetOrgMesh(frame->pFrameSibling);

		if (mesh) {
			return mesh;
		}
	}
	if (frame->pFrameFirstChild != NULL)
	{
		//子供。
		LPD3DXMESH mesh = GetOrgMesh(frame->pFrameFirstChild);
		if (mesh) {
			return mesh;
		}
	}

	return NULL;
}