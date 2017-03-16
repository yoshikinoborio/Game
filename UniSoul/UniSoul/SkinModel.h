#pragma once
#include "Animation.h"
#include "SkinModelData.h"
#include "SkinModelDataResources.h"
#include "Light.h"

class SkinModelData;
class SkinModelDataResources;

	//スキンモデル。
class SkinModel {
public:
	//コンストラクタ。
	SkinModel();

	//デストラクタ。
	~SkinModel();

	//初期化。
	void Initialize(SkinModelData* modelData);

	//描画。
	void Draw(D3DXMATRIX* viewMatrix, 
		D3DXMATRIX* projMatrix, 
		bool isDrawToShadowMap);
	/*!
	*@brief	更新。
	*@details
	*@param[in]		trans	平行移動。
	*@param[in]		rot		回転。
	*@param[in]		scale	拡大。
	*/
	void Update(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);

	/*!
	* @brief	距離フォグパラメータを設定。
	*@param[in]	param0		フォグパラメータ0
	*フォグが掛かり始める距離。
	*@param[in]	param1		フォグパラメータ１
	*フォグが掛かり切る距離。
	*/
	void SetFogDistParam(float param0,float param1)
	{
		m_fogDistParam[0] = param0;
		m_fogDistParam[1] = param1;
	}

	//距離フォグのフラグを設定。
	void SetFogDistFlag(int flag)
	{
		m_fogDistFlag = flag;
	}

	/*!
	* @brief	高さフォグパラメータを設定。
	*@param[in]	param0		フォグパラメータ0
	*フォグが掛かり始める高さ。
	*@param[in]	param1		フォグパラメータ１
	*フォグが掛かり切る高さ。
	*/
	void SetFogHeightParam(float param0,float param1)
	{
		m_fogHeightParam[0] = param0;
		m_fogHeightParam[1] = param1;
	}

	//高さフォグのフラグを設定。
	void SetFogHeightFlag(int flag)
	{
		m_fogHeightFlag = flag;
	}

	void DrawMeshContainer(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXMESHCONTAINER pMeshContainerBase,
		LPD3DXFRAME pFrameBase,
		ID3DXEffect* effect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		Light*		light,
		bool isDrawToShadowMap
		);
	void DrawFrame(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXFRAME pFrame,
		ID3DXEffect* effect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		Light*		light,
		bool isDrawToShadowMap
		);
	//ライトの設定。
	void SetLight(Light* light)
	{
		this->m_light = light;
	}
	//シャドウレシーバーのフラグを設定。
	void SetShadowReceiverFlag(bool flag)
	{
		m_isShadowReceiver = flag;
	}
	D3DXMATRIX& GetWorldMatrix()
	{
		return m_worldMatrix;
	}
	//法線マップのロード。
	//プレイヤーの法線マップを読み込む用の関数。
	void LoadNormalMap(const char* filePath, const char* BoneName);
	//プレイヤー以外の時に使うよう。
	void LoadNormalMap(const char* filePath);

	//法線マップの保持フラグを設定。
	void SetHasNormalMap(bool hasNormalMap)
	{
		m_hasNormalMap = hasNormalMap;
	}
	LPD3DXMESH GetOrgMeshFirst();
private:
	D3DXMATRIX				m_worldMatrix;				//ワールド行列。
	D3DXMATRIX				m_rotationMatrix;			//回転行列。
	SkinModelData*			m_skinModelData;			//スキンモデルデータ。
	Animation				m_animation;				//アニメーション。
	static const int		MAX_MATRIX_PALLET = 128;	//マトリクスパレットの最大数。
	D3DXMATRIX				m_boneMatrixPallet[MAX_MATRIX_PALLET];	//マトリクスパレット。
	ID3DXEffect*			m_effect;					//エフェクト。
	ID3DXEffect*			m_shadoweffect;				//シャドウエフェクト。
	Light*					m_light;					//ライト。
	bool					m_isShadowReceiver;			//シャドウレシーバー。
	D3DXMATRIX				m_LVP;						//ライトビュープロジェクション行列。
	LPDIRECT3DTEXTURE9		m_normalMap = NULL;			//法線マップのテクスチャ。
	LPDIRECT3DTEXTURE9		m_normalMap2 = NULL;		//法線マップ(プレイヤーの頭)のテクスチャ。
	LPDIRECT3DTEXTURE9		m_normalMap3 = NULL;		//法線マップ(プレイヤーの体)のテクスチャ。
	bool					m_hasNormalMap = FALSE;		//法線マップを保持している(フラグ)？
	float					m_fogDistParam[2];			//距離フォグのパラメータ。
	int						m_fogDistFlag;				//距離フォグを掛けないか掛けるかのフラグ。
	float					m_fogHeightParam[2];		//高さフォグのパラメータ。
	int						m_fogHeightFlag;			//高さフォグを掛けないか掛けるかのフラグ。
};