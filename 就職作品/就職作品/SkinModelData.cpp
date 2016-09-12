#include "stdafx.h"
#include "SkinModelData.h"
#include "Animation.h"

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
	// �t���[���K�w�̌������ꂽ�g�����X�t�H�[���s����X�V
	//--------------------------------------------------------------------------------------
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, const D3DXMATRIX* pParentMatrix)
	{
		D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;

		// �t���[���ɂ���s�񂩂烏�[���h�ϊ��s��𐶐�
		if (pParentMatrix != NULL)
			D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix,
			&pFrame->TransformationMatrix,
			pParentMatrix);
		else
			pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
		//�Z��t���[���̍s������[���h�ϊ��s���
		if (pFrame->pFrameSibling != NULL)
		{
			UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
		}
		//�q�t���[�����̍s������[���h�ϊ��s���
		if (pFrame->pFrameFirstChild != NULL)
		{
			UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
		}
	}

	//�A�j���[�V��������у����_�����O�̂��߂̃��b�V���K�w���Z�b�g�A�b�v
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
				//CloneMeshFVF(���b�V���̍쐬�I�v�V�������w��,
				//�o�̓��b�V���Ɋ܂܂�钸�_�̒��_�t�H�[�}�b�g���w��,
				//���b�V���Ɋ֘A�t�����Ă���f�o�C�X �I�u�W�F�N�g,
				//�R�s�[���ꂽ���b�V��,)�_��Ȓ��_�t�H�[�}�b�g (FVF) �R�[�h���g���ă��b�V���̃R�s�[���쐬����
				//�߂�l�͐��������ꍇ�́AD3D_OK
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
	//�֐������Ń��[�g�t���[������q�t���[�����������Ȃ���A���b�V���������t���[����T�����āA�����Ɋi�[����Ă���u�{�[���v�̏����i�[���Ă���
	//--------------------------------------------------------------------------------------
	HRESULT SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME rootFrame)
	{
		UINT iBone, cBones;
		D3DXFRAME_DERIVED* pFrame;

		//MeshContainer�̓��b�V���Ɋ܂܂��{�[���Ȃǂ̐F�X�ȏ����i�[���Ă���
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

		// if there is a skinmesh, then setup the bone matrices
		//�A�j���[�V�������邩���Ȃ����̔���
		if (pMeshContainer->pSkinInfo != NULL)
		{
			cBones = pMeshContainer->pSkinInfo->GetNumBones();

			pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[cBones];
			if (pMeshContainer->ppBoneMatrixPtrs == NULL)
				return E_OUTOFMEMORY;

			for (iBone = 0; iBone < cBones; iBone++)
			{
				//���b�V�����ǂ̃{�[�����g������D3DXFrameFind(�q�t���[�������������ꍇ�͂����Ԃ�)���g���ĒT���Đݒ肵�Ă���
				pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(rootFrame,
					pMeshContainer->pSkinInfo->GetBoneName(iBone));
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
	//���[�v�ɂ���ăt���[���Ɋi�[����Ă��郁�b�V���R���e�i���i�[
	//--------------------------------------------------------------------------------------
	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME pFrame, LPD3DXFRAME pRootFrame)
	{
		HRESULT hr;

		//�e�t���[��
		if (pFrame->pMeshContainer != NULL)
		{
			hr = SetupBoneMatrixPointersOnMesh(pFrame->pMeshContainer, pRootFrame);
			if (FAILED(hr))
				return hr;
		}

		//�Z��t���[��
		if (pFrame->pFrameSibling != NULL)
		{
			hr = SetupBoneMatrixPointers(pFrame->pFrameSibling, pRootFrame);
			if (FAILED(hr))
				return hr;
		}

		//�q�t���[��
		if (pFrame->pFrameFirstChild != NULL)
		{
			hr = SetupBoneMatrixPointers(pFrame->pFrameFirstChild, pRootFrame);
			if (FAILED(hr))
				return hr;
		}

		return S_OK;
	}
	//ID3DXAllocateHierarchy�̓��[�U�̎������K�v
	//�C���^�[�t�F�C�X�͎��̂������Ȃ����ۃN���X�A���ۃN���X���A
	//ID3DXAllocateHierarchy AlllocHrcy;
	//�Ǝ��̂�錾����ƁA�R���p�C�����璊�ۃI�u�W�F�N�g�͎��̉��ł��Ȃ��Ɠ{����
	//������
	//ID3DXAllocateHierarchy *pAlllocHrcy;
	//�ƃ|�C���^�錾���邱�Ƃ͉\�i�|�C���^�͎��̂ł͂Ȃ�����j�������A
	//�����D3DXLoadMeshHierarchyFromX�֐��ɓn���\���ɏo��ƁA�֐������Ń|�C���^���Q�Ƃ��ꂽ�u�ԃ������ی�ᔽ�ŃA�v���P�[�V�������~�܂�A�܂�A
	//ID3DXAllocateHierarchy����N���X��h�����āA��`����Ă��鉼�z�֐������ۂɎ�������K�v������
	//ID3DXAllocateHierarchy�̓I�u�W�F�N�g�̍쐬�ƍ폜��S���������
	class AllocateHierarchy : public ID3DXAllocateHierarchy
	{
	public:
		//���������Ȃ��ƃG���[�ɂȂ�
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
	// Name: AllocateHierarchy::CreateFrame(�{�[���̃c���[�K�w������Ă���(�e����q�A�q���瑷�݂�����))
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
		//�{�[���̂ƍ����s��̏�����
		D3DXMatrixIdentity(&pFrame->TransformationMatrix);
		D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);

		//���Ɏq�Ƒ��̃t���[���̏�����
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
	//���b�V���R���e�i(D3DXMESHCONTAINER�\����)���쐬
	// Desc: 
	//--------------------------------------------------------------------------------------
	HRESULT AllocateHierarchy::CreateMeshContainer(
		LPCSTR Name,									//���b�V���̖��O
		CONST D3DXMESHDATA *pMeshData,					//���b�V�� �f�[�^�\���̂ւ̃|�C���^�[
		CONST D3DXMATERIAL *pMaterials,					//���b�V���Ɏg�p����}�e���A���̔z��
		CONST D3DXEFFECTINSTANCE *pEffectInstances,		//���b�V���Ɏg�p����G�t�F�N�g �C���X�^���X�̔z��
		DWORD NumMaterials,								//�}�e���A���z����̃}�e���A����
		CONST DWORD *pAdjacency,						//���b�V���̗אڃ|���S���C���f�b�N�X�̔z��
		LPD3DXSKININFO pSkinInfo,						//�X�L���f�[�^�����������ꍇ�̃X�L�����b�V���I�u�W�F�N�g�ւ̃|�C���^�[
		LPD3DXMESHCONTAINER *ppNewMeshContainer)		//�쐬���ꂽ���b�V���R���e�i�[��Ԃ�
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
		//�ʏ탁�b�V�����ǂ���
		if (pMeshData->Type != D3DXMESHTYPE_MESH)
		{
			hr = E_FAIL;
			goto e_Exit;
		}

		// get the pMesh interface pointer out of the mesh data structure
		pMesh = pMeshData->pMesh;
		DWORD numVert = pMesh->GetNumVertices();
		// this sample does not FVF compatible meshes, so fail when one is found
		//���b�V���ɉ����񂪓����Ă��Ȃ��ꍇ�̃G���[
		if (pMesh->GetFVF() == 0)
		{
			hr = E_FAIL;
			goto e_Exit;
		}

		// allocate the overloaded structure to return as a D3DXMESHCONTAINER
		// ���b�V���R���e�i�I�u�W�F�N�g�̐���
		pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
		if (pMeshContainer == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}
		memset(pMeshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

		// make sure and copy the name.  All memory as input belongs to caller, interfaces can be addref'd though
		//���������m�ۂ��ĕ�������i�[���� ( �t���[�����̖��O�i�[�p )
		hr = AllocateName(Name, &pMeshContainer->Name);
		//// �������m�ێ��s
		if (FAILED(hr))
			goto e_Exit;

		pMesh->GetDevice(&pd3dDevice);
		//���b�V���Ɋ܂܂��|���S���̐����擾���܂�
		NumFaces = pMesh->GetNumFaces();

		pMeshContainer->MeshData.pMesh = pMesh;
		//���b�V���R���e�i�ɒʏ탁�b�V����ݒ�
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		//�Q�ƃJ�E���^��1���₷�K�v������
		//�����e�N�X�`���ȂǃC���X�^���X�����g���Ă��邩���Ǘ����Ă���
		//���Z�̓C���X�^���X�̃f�X�g���N�^���Ă΂ꂽ���ɍs����
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
		//�͂���1�̎O�p�|���S���ɗאڂ���3�̃|���S���C���f�b�N�X�ԍ����i�[�����אڃ|���S���C���f�b�N�X
		pMeshContainer->pAdjacency = new DWORD[NumFaces * 3];
		if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}

		// �אڏ����R�s�[
		memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD)* NumFaces * 3);
		memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9)* pMeshContainer->NumMaterials);

		// if materials provided, copy them
		// �󂯎�����}�e���A�����R�s�[����
		if (NumMaterials > 0)
		{
			// �܂��͊ۂ��ƃR�s�[
			memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL)* NumMaterials);

			//// �e�N�X�`������ۑ�����
			for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
			{
				if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
				{
					char* baseDir = "image/";
					char filePath[64];
					strcpy(filePath, baseDir);
					strcat(filePath, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
					//�t�@�C������ɂ��ăe�N�X�`�����쐬����
					if (FAILED(D3DXCreateTextureFromFile(
						pd3dDevice,
						filePath,//�t�@�C�������w�肷�镶����ւ̃|�C���^�B�R���p�C���̐ݒ肪Unicode��v�����Ă���ꍇ�A�f�[�^�^�C�vLPCTSTR��LPCWSTR�ɂȂ�B����ȊO�̏ꍇ�́A���̕�����̃f�[�^�^�C�v��LPCSTR 
						&pMeshContainer->ppTextures[iMaterial]))//�쐬���ꂽ�L���[�u �e�N�X�`�� �I�u�W�F�N�g��\���AIDirect3DTexture9 �C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
						) {
						pMeshContainer->ppTextures[iMaterial] = NULL;
					}

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

		// if there is skinning information, save off the required data and then setup for HW skinning
		if (pSkinInfo != NULL)
		{
			// first save off the SkinInfo and original mesh data
			//// �X�L�������i�[
			pMeshContainer->pSkinInfo = pSkinInfo;
			pSkinInfo->AddRef();

			pMeshContainer->pOrigMesh = pMesh;
			pMesh->AddRef();

			// Will need an array of offset matrices to move the vertices from the figure space to the bone's space
			// ���̂̃��[�J����Ԃ���{�[����Ԃɒ��_���ړ����邽�߂̃I�t�Z�b�g�s��p�̔z���p�ӂ���
			cBones = pSkinInfo->GetNumBones();
			pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[cBones];
			if (pMeshContainer->pBoneOffsetMatrices == NULL)
			{
				hr = E_OUTOFMEMORY;
				goto e_Exit;
			}

			// get each of the bone offset matrices so that we don't need to get them later
			// ���ꂼ��̃{�[���̃I�t�Z�b�g�s��(�{�[���̋t�s��)�����o���ĕۑ�����
			//���������_�Ƀ{�[�����ړ��A��]������悤�ɂ��邩�琳�����ړ��ʂœ���
			for (iBone = 0; iBone < cBones; iBone++)
			{
				pMeshContainer->pBoneOffsetMatrices[iBone] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
			}

			// GenerateSkinnedMesh will take the general skinning information and transform it to a HW friendly version
			// �X�L�����b�V�����쐬����
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
			//D3DXComputeTangentFrameEx�̓��b�V���̐ڐ��t���[���̌v�Z�����s���A�ڐ��x�N�g��(�|���S���̌����ɒ��s����x�N�g��)�A�]�@���x�N�g��(�|���S���̌����ƃ|���S���̌����ɒ��s����x�N�g���ɒ��s����x�N�g��)�A����ѕK�v�ɉ����Ė@���x�N�g��(�|���S���̌���)�����������
			hr = D3DXComputeTangentFrameEx(
				pOutMesh,				// ID3DXMesh���b�V���I�u�W�F�N�g�ւ̃|�C���^
				D3DDECLUSAGE_TEXCOORD,	//�e�N�X�`���[���W�̓��̓Z�}���e�B�N�X���w�肷��AD3DX_DEFAULT���w�肷��Ƃ��̊֐��̓e�N�X�`���[���W���Ȃ����̂ƌ��Ȃ��A�@���x�N�g���v�Z���w�肳��Ȃ�����֐��͎��s����
				0,						//���b�V���ɕ����̃e�N�X�`���[���W������ꍇ�ɁA�ڐ��t���[���̌v�Z�Ɏg�p����e�N�X�`���[���W���w�肷��B0 �̏ꍇ�A���b�V���ɂ̓e�N�X�`���[���W��1�����Ȃ�
				D3DDECLUSAGE_TANGENT,	//�o�̓Z�}���e�B�N�X(�Z�}���e�B�N�X(�Ӗ�)�A���̏��͉��Ȃ̂��ƌ�������t�^���Ă���ATANGENT�Ȃ�ڐ�)�̃^�C�v���w�肷��B�ʏ�AU�e�N�X�`���[���W����Ƃ���Δ������i�[����邱�Ƃ�\��D3DDECLUSAGE_TANGENT���w�肷��BD3DX_DEFAULT�̏ꍇ�A���̕Δ����͊i�[����܂���
				0,						//U �e�N�X�`���[���W����Ƃ���Δ������i�[����Z�}���e�B�N�X �C���f�b�N�X���w�肷��
				D3DX_DEFAULT,			//D3DDECLUSAGE�^���w�肷��B�ʏ�AV �e�N�X�`���[���W����Ƃ���Δ������i�[����邱�Ƃ�\��D3DDECLUSAGE_BINORMAL���w�肷��BD3DX_DEFAULT�̏ꍇ�A���̕Δ����͊i�[����Ȃ�
				0,						//V�e�N�X�`���[���W����Ƃ���Δ������i�[����Z�}���e�B�N�X�C���f�b�N�X���w�肷��
				D3DDECLUSAGE_NORMAL,	//�o�͕W���Z�}���e�B�N�X���w�肷��B�ʏ�A���_���Ƃ̖@���x�N�g�����i�[����邱�Ƃ�\��D3DDECLUSAGE_NORMAL���w�肷��BD3DX_DEFAULT�̏ꍇ�A���̖@���x�N�g���͊i�[����Ȃ�
				0,						//���_���Ƃ̖@���x�N�g�����i�[����Z�}���e�B�N�X �C���f�b�N�X���w�肷��
				0,						//�ڐ��t���[���̌v�Z�̃I�v�V�������w�肷��
				NULL,					//�ʂ��Ƃ�3�� WORD�l���i�[����z��ւ̃|�C���^�[
				0.01f,    //�{�P�.�l��������������Ƃڂ��Ȃ��Ȃ�
				0.25f,
				0.01f,
				&pOutMesh,	//�Z�o���ꂽ�ڐ��x�N�g���A�]�@���x�N�g���A����і@���x�N�g���̃f�[�^���󂯎��o��ID3DXMesh���b�V���I�u�W�F�N�g�ւ̃|�C���^�[�̃A�h���X
				NULL		//���̃��\�b�h�Ōv�Z�����V�������_���猳�̒��_�ւ̃}�b�s���O���󂯎��o��ID3DXBuffer�o�b�t�@�[�I�u�W�F�N�g�ւ̃|�C���^�[�̃A�h���X�A�o�b�t�@�[�� DWORD�̔z��ł���A�z��̃T�C�Y��ppMeshOut�̒��_�̐��Ƃ��Ē�`�����
				);
			pMeshContainer->MeshData.pMesh->Release();
			pMeshContainer->MeshData.pMesh = pOutMesh;


			//std::vector<DWORD> adjList;
			//adjList.resize(3 * pOutMesh->GetNumFaces());
			////���b�V���G�b�W�̃��X�g�ƁA�e�G�b�W�����L����ʂ̃��X�g�𐶐�����
			//pOutMesh->GenerateAdjacency(1.0f / 512.0f, &adjList[0]); // EPSION�͓K���Ȓl(1.0f/512�Ƃ�)

			//DWORD numVert = pOutMesh->GetNumVertices();  // Optimize�̈��
			//pOutMesh->OptimizeInplace(D3DXMESHOPT_COMPACT, &adjList[0], NULL, NULL, NULL);
			//numVert = pOutMesh->GetNumVertices();
			//���̃R�����g�A�E�g����Ă���v���O�������g���ƃ������[���[�N�������N��

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
				0.01f,    //�{�P�.�l��������������Ƃڂ��Ȃ��Ȃ�
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
			////���X�g�̃T�C�Y���v�����ꂽ�T�C�Y (_Newsize) �����������ꍇ�́A�v�����ꂽ�T�C�Y�ɂȂ�܂ŁA���X�g�ɗv�f���ǉ������  
			////���X�g�̃T�C�Y���v�����ꂽ�T�C�Y�����傫���ꍇ�́A���X�g�̃T�C�Y�� _Newsize �ɂȂ�܂ŁA���X�g�̖����ɋ߂��v�f���珇�ɍ폜�����
			////���X�g�̌��݂̃T�C�Y���v�����ꂽ�T�C�Y�Ɠ����ꍇ�́A�������s����Ȃ�
			//adjList.resize(3 * pOutMesh->GetNumFaces());
			////���b�V���G�b�W�̃��X�g(�e�G�b�W�Ɍq�����Ă�|���S���̏��)�ƁA�e�G�b�W�����L����ʂ̃��X�g�𐶐�����
			//pOutMesh->GenerateAdjacency(1.0f, &adjList[0]); // EPSION�͓K���Ȓl(1.0f/512�Ƃ�)
			//numVert = pOutMesh->GetNumVertices();  // Optimize�̈��
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
		SAFE_DELETE_ARRAY(pFrameToFree->Name);	//char�^�̔z��Ƃ��ē��I�Ƀ��������m�ۂ��Ă���̂�delete����K�v������
		SAFE_DELETE(pFrameToFree);
		return S_OK;
	}




	//--------------------------------------------------------------------------------------
	// Name: AllocateHierarchy::DestroyMeshContainer()
	//��R�̃����������܂��܂Ɗm�ۂ��Ă���̂ŁA�R�炷���ƂȂ������Ȃ��Ƃ����Ȃ�
	// Desc: 
	//--------------------------------------------------------------------------------------
	HRESULT AllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
	{
		UINT iMaterial;
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

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
		return S_OK;
	}


}
SkinModelData::SkinModelData() :
m_frameRoot(nullptr),
m_pAnimController(nullptr)
{
}
SkinModelData::~SkinModelData()
{
}
void SkinModelData::Release()
{
	if (m_pAnimController) {
		m_pAnimController->Release();
	}
}

void SkinModelData::LoadModelData(const char* filePath, Animation* anim)
{
	AllocateHierarchy alloc;
	//x�t�@�C�����ɒ�`����Ă���|���S�����b�V���̃t���[���K�w��ǂݍ���Ŋi�[����֐�(x�t�@�C������A�j���[�V�����������o��)
	HRESULT hr = D3DXLoadMeshHierarchyFromX(
		filePath,	//x�t�@�C���̃t�@�C���p�X
		D3DXMESH_VB_MANAGED,	//���b�V���쐬�̃I�v�V�����AD3DXMESH_MANAGED���w�肷��̂���ʓI�ADirect3D���Ǘ����郁�������ɍ쐬
		g_pd3dDevice,	//�f�o�C�X�ւ̃|�C���^
		&alloc,			//ID3DXAllocateHierarchy�C���^�[�t�F�C�X�ւ̃|�C���^(�w��x�t�@�C������t���[���K�w���\�z)
		nullptr,		//x�t�@�C�����Ƀ��[�U��`����������Ƃ��A���̏��������Ɋi�[
		&m_frameRoot,	//D3DXFRAME�\���̂ւ̃_�u���|�C���^�ŁA�����Ƀt���[���K�w�̐e���i���[�g�t���[���j�ւ̃|�C���^�̃|�C���^���Ԃ�A���̃|�C���^��ʂ��Ďq�t���[���ɃA�N�Z�X�ł���A�v����Ƀt���[���K�w�̑S�Ă��i�[�����
		&m_pAnimController	//ID3DXAnimationController�C���^�[�t�F�C�X�ւ̃|�C���^�ŁAx�t�@�C�����̃A�j���[�V�����ɑΉ�����A�j���[�V�����R���g���[���ւ̃|�C���^���Ԃ�
		);
	//m_m_pAnimController->(0);
	SetupBoneMatrixPointers(m_frameRoot, m_frameRoot);
	if (anim && m_pAnimController) {
		anim->Initialize(m_pAnimController);
	}
}

void SkinModelData::UpdateBoneMatrix(const D3DXMATRIX& matWorld)
{
	UpdateFrameMatrices(m_frameRoot, &matWorld);
}