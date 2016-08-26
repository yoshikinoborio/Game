#include "stdafx.h"
#include "Model3D.h"

Model3D::Model3D()
{
	m_mesh = NULL;
	m_textures = NULL;
	m_numMaterial = 0;
	m_effect = NULL;
}

Model3D::~Model3D()
{
	Release();
}

//初期化
void Model3D::Initialize(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR name)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;	//マテリアルバッファ

	//Xファイルのロード。
	D3DXLoadMeshFromX(
		name,	//Xファイルへの相対または絶対パス
		D3DXMESH_SYSTEMMEM,		//頂点、インデックスバッファが何のメモリを使うかを指定する
		pd3dDevice,				//D3Dのデバイスへのポインタ
		NULL,					//ポリゴンの隣接情報の出力先
		&pD3DXMtrlBuffer,		//マテリアルバッファの出力先
		NULL,					//今回も今後も使う事が無いと思うのでNULL
		&m_numMaterial,			//マテリアルの数の出力先
		&m_mesh					//Xファイルから作成されたID3DXMeshのインスタンスの格納先
		);

	// マテリアルバッファを取得。
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	m_textures = new LPDIRECT3DTEXTURE9[m_numMaterial];
	//マテリアルの数だけループを回してテクスチャをロード
	for (DWORD i = 0; i < m_numMaterial; i++)
	{
		m_textures[i] = NULL;
		//画像ファイルからテクスチャを作成する。
		D3DXCreateTextureFromFileA(pd3dDevice,	//デバイスのポインタ
			d3dxMaterials[i].pTextureFilename,	//画像ファイルへの相対または絶対パス
			&m_textures[i]);					//生成されたテクスチャオブジェクトのポインタが返る
	}
	// マテリアルバッファを解放。
	pD3DXMtrlBuffer->Release();

	LPD3DXBUFFER  compileErrorBuffer = NULL;

	//シェーダーをコンパイル。
	HRESULT hr = D3DXCreateEffectFromFile(
		pd3dDevice,								//いつものデバイスのポインタ
		"basic.fx",								//シェーダプログラムが書き込まれたファイルへの相対または絶対パス
		NULL,									//プリプロセッサの定義
		NULL,									//ID3DXIncludeインターフェイスの定義
		D3DXSHADER_SKIPVALIDATION,				//シェーダーコンパイル時のコンパイルオプションを指定
		NULL,									//エフェクト間で共有するグローバル変数をとりまとめてくれるID3DXEffectPoolインターフェイスを渡す
		&m_effect,								//ID3DXEffectのインスタンス
		&compileErrorBuffer						//コンパイルエラーが起こった時のエラー情報が格納される
		);
	if (hr != S_OK) {
		//シェーダーのエラー表示
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}

//描画
void Model3D::Draw(LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	D3DXMATRIX	m_world,
	D3DXMATRIX	m_rotation,
	int numDiffuseLight)
{
	m_effect->SetTechnique("SkinModel");
	m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_effect->BeginPass(0);

	//定数レジスタに設定するカラー。
	D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
	//ワールド行列の転送。
	m_effect->SetMatrix("g_worldMatrix", &m_world);
	//ビュー行列の転送。
	m_effect->SetMatrix("g_viewMatrix", &viewMatrix);
	//プロジェクション行列の転送。
	m_effect->SetMatrix("g_projectionMatrix", &projMatrix);	
	//回転行列を転送。
	m_effect->SetMatrix("g_rotationMatrix", &m_rotation);		
	//ライトの向きを転送。
	m_effect->SetVectorArray("g_diffuseLightDirection", diffuseLightDirection, numDiffuseLight);
	//ライトのカラーを転送。
	m_effect->SetVectorArray("g_diffuseLightColor", diffuseLightColor, numDiffuseLight);
	//環境光を設定。
	m_effect->SetVector("g_ambientLight", &ambientLight);

	m_effect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。

	for (DWORD i = 0; i < m_numMaterial; i++)
	{
		m_effect->SetTexture("g_diffuseTexture", m_textures[i]);
		// Draw the m_mesh subset
		m_mesh->DrawSubset(i);
	}

	m_effect->EndPass();
	m_effect->End();
}

//解放
void Model3D::Release()
{
	//メッシュを開放。
	if (m_mesh != NULL) {
		m_mesh->Release();
		m_mesh = NULL;
	}
	//テクスチャを開放。
	if (m_textures != NULL) {
		for (unsigned int i = 0; i < m_numMaterial; i++) {
			if (m_textures[i] != NULL) {
				m_textures[i]->Release();
				m_textures[i] = NULL;
			}
		}
		delete[] m_textures;
		m_textures = NULL;
	}
	//エフェクトを開放。
	if (m_effect != NULL) {
		m_effect->Release();
		m_effect = NULL;
	}
}