#pragma once
#include "Animation.h"
#include "SkinModelData.h"

class SkinModelData;
class Light;

	//スキンモデル
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	//初期化
	void Initialize(SkinModelData* modelData);
	//描画
	void Draw(D3DXMATRIX* viewMatrix, 
		D3DXMATRIX* projMatrix, 
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight);
	/*!
	*@brief	更新。
	*@details
	*@param[in]		trans	平行移動。
	*@param[in]		rot		回転。
	*@param[in]		scale	拡大。
	*/
	void Update(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);

	void DrawMeshContainer(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXMESHCONTAINER pMeshContainerBase,
		LPD3DXFRAME pFrameBase,
		ID3DXEffect* effect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
	void DrawFrame(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXFRAME pFrame,
		ID3DXEffect* effect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
	//ライトの設定
	void SetLight(Light* light)
	{
		this->m_light = light;
	}
private:
	D3DXMATRIX				m_worldMatrix;		//ワールド行列
	D3DXMATRIX				m_rotationMatrix;	//回転行列
	SkinModelData*			m_skinModelData;	//スキンモデルデータ。
	Animation				m_animation;		//アニメーション
	static const int		MAX_MATRIX_PALLET = 128;	//マトリクスパレットの最大数
	D3DXMATRIX				m_boneMatrixPallet[MAX_MATRIX_PALLET];	//マトリクスパレット
	ID3DXEffect*			m_effect;			//エフェクト
	Light*					m_light;			//ライト。
};