#pragma once
#include "AnimationModel3D.h"

class Camera;

class UnityChan : AnimationModel3D
{
public:
	UnityChan();
	~UnityChan();
	//初期化。
	void Initialize()override;
	//更新。
	void Update()override;
	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
		bool isShadowReceiver);
	//解放。
	void Release();
	//パッドによるカメラの奥に移動する処理。
	void PadMove();
	D3DXVECTOR3 GetUnityChanPos()
	{
		return m_position;
	}
	D3DXMATRIX GetUnityChanWorld()
	{
		return m_world;
	}
	D3DXVECTOR3 GetUnityiChanScale()
	{
		return m_scale;
	}
	D3DXQUATERNION GetUnityiChanRotation()
	{
		return m_rotation;
	}
private:
	enum AnimationNo {
		AnimationInvalid = -1,
		AnimationStand,		//立ち。
		AnimationWalk,		//歩き。
		AnimationRun,		//走り。
		AnimationJump,		//ジャンプ。
	};
	D3DXVECTOR3		m_position;			//座標。
	D3DXVECTOR3     m_scale;			//スケール。
	D3DXMATRIX		m_world;			//ワールド行列。
	Camera*         m_camera;			//カメラのインスタンス。
	AnimationNo		m_currentAnimSetNo;
	D3DXQUATERNION  m_rotation;			//回転行列。
	int				m_animationcount;
};
