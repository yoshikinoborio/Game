#pragma once
#include "AnimationModel3D.h"
#include "CharacterController.h"
#define WALKSPEED 0.02f	//歩くスピード。
#define RUNSPEED 0.2f*60.0f	//走るスピード。
#define MAX_RUN 0.6f*60.0f	//歩きまでの上限値。

class Camera;

class UnityChan : public AnimationModel3D
{
public:
	UnityChan();
	~UnityChan();
	//初期化。
	void Initialize();
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
	//プレイヤーで再生されるアニメーションの種類。
	enum PlayerAnimationNo {
		AnimationInvalid = -1,
		AnimationWait_00,	//待機(立ち)。
		AnimationWalk,		//歩き。
		AnimationRun,		//走り。
		AnimationWait_01,	//待機(腕伸ばし)。
		AnimationWait_02,	//待機(クルクル)。
		AnimationSLID,		//スライディング。
		AnimationBackStep,	//バックステップ。
	};
	//プレイヤーの状態遷移の種類。
	enum PlayerState{
		StateWait_00 = 0,	//待機(立ち)。
		StateWait_01,		//待機(腕伸ばし)。
		StateWait_02,		//待機(クルクル)。
		StateWalk,          //歩き。
		StateRun,			//走り。
		StateSLID,			//スライディング。
		StateBackStep,		//バックステップ。
	};

private:
	D3DXVECTOR3		m_position;					//座標。
	D3DXVECTOR3     m_scale;					//スケール。
	D3DXMATRIX		m_world;					//ワールド行列。
	Camera*         m_camera;					//カメラのインスタンス。
	PlayerAnimationNo	m_currentAnimSetNo;		//現在再生しているアニメーション。
	PlayerState     m_state;					//プレイヤーの状態。
	D3DXQUATERNION  m_rotation;					//回転行列。
	D3DXVECTOR3     m_moveDir;					//カメラから求めた方向。
	float           m_moveSpeed;				//移動速度(歩く時と走る時の速度調整用)。
	float           m_waitAnimetionChangeTime;	//待機アニメーションの切り替え時間。
	float			m_currentAngleY;			//現在の方向。
	float			m_targetAngleY;				//向きたい方向。
	bool			m_isTurn;					//回転フラグ。
	float           m_saveLStickX;				//左スティックの左右の入力量を格納。
	float			m_saveLStickY;				//左スティックの前後の入力量を格納。
	CharacterController m_characterController;	//キャラクタコントローラ。
	float			m_height;					//ユニティちゃんの高さ。
	float			m_radius;					//ユニティちゃんの半径。
	D3DXVECTOR3		m_moveDirSpeed;				//移動量。
};
