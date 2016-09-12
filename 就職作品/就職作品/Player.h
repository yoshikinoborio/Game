#pragma once
#include "Model3D.h"
#include "SkinModel.h"
#include "SkinModelData.h"

class Camera;

//プレイヤークラス
class Player
{
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//初期化
	void Initialize(LPDIRECT3DDEVICE9 pd3dDevice);
	//更新
	void Update();
	//描画
	void Draw(LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight);
	//解放
	void Release();
	D3DXVECTOR3 GetPlayerPos()
	{
		return m_position;
	}
	//パッドによるカメラの奥に移動する処理
	void PadMove();
private:
	enum AnimationNo {
		AnimationInvalid = -1,
		AnimationStand,		//立ち
		AnimationWalk,		//歩き
		AnimationRun,		//走り
		AnimationJump,		//ジャンプ
	};
	Model3D			m_model3d;			//3D関係を表示するModel3Dのインスタンスを保持
	D3DXVECTOR3		m_position;			//座標
	D3DXVECTOR3     m_scale;			//スケール
	D3DXMATRIX		m_world;			//ワールド行列
	//D3DXMATRIX		m_rotation;		//回転行列
	Camera*         m_camera;			//カメラのインスタンス
	SkinModelData	m_skinModelData;	//スキンモデルデータ
	SkinModel		m_skinModel;		//スキンモデル
	Animation		m_animation;		//アニメーション
	AnimationNo		m_currentAnimSetNo;
	D3DXQUATERNION  m_rotation;			//回転行列
};
