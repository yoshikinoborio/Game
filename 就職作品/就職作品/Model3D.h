#pragma once

//3Dモデルのクラス
class Model3D
{
public:
	//コンストラクタ
	Model3D();

	//デストラクタ
	~Model3D();

	//初期化
	void Initialize(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR name);

	//描画
	void Draw(LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		D3DXMATRIX	m_world,
		D3DXMATRIX	m_rotation,
		int numDiffuseLight);

	//解放
	void Release();
private:
	LPD3DXMESH				m_mesh;				//メッシュ。
	LPDIRECT3DTEXTURE9*		m_textures;			//テクスチャ。
	DWORD					m_numMaterial;		//マテリアルの数。
	ID3DXEffect*			m_effect;			//エフェクト。
};