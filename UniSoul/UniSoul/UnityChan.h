#pragma once
#include "AnimationModel3D.h"
#include "CharacterController.h"
#include "ParticleEmitter.h"
#include "SoundSource.h"
#include "Light.h"
#define WALKSPEED 0.02f*60.0f	//歩くスピード。
#define RUNSPEED 0.2f*60.0f	//走るスピード。
#define MAX_RUN 0.6f*60.0f	//歩きまでの上限値。
#define MAX_LEVEL 100

class CParticleEmitter;
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
		bool isShadowReceiver);
	//解放。
	void Release();
	//パッドによるカメラの奥に移動する処理。
	void PadMove();
	//動いている状態での処理。
	void StateMove();
	//ジャンプ処理。
	void Jump();
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
	D3DXVECTOR3 GetUniDir()
	{
		return m_UniDir;
	}
	//HPの取得。
	int GetHP()
	{
		return m_hp;
	}
	//最大HPの取得。
	int GetMaxHP()
	{
		return m_maxhp;
	}
	//経験値の加算
	void AddPlayerEXP(int EXP)
	{
		m_getEXP += EXP;
	}
	//プレイヤーのレベルの取得。
	int GetLv()
	{
		return m_lv;
	}
	void Damage();
	//プレイヤーで再生されるアニメーションの種類。
	enum PlayerAnimationNo {
		AnimationWait_00 = 0,	//待機(立ち)。
		AnimationWalk,		//歩き。
		AnimationRun,		//走り。
		AnimationWait_01,	//待機(腕伸ばし)。
		AnimationWait_02,	//待機(クルクル)。
		AnimationSLID,		//スライディング。
		AnimationBackStep,	//バックステップ。
		AnimationFall,		//落下中。
		AnimationLanding,	//着地。
		AnimationJump,		//ジャンプ。
		AnimationPunch,		//パンチ。
		AnimationRKick,		//右上段蹴り。
		AnimationRotationKick,//回し蹴り。
		AnimationSomersault,//サマーソルト。
		AnimationFightingPause,//戦闘での待機。
		AnimationFightingRun,//戦闘での走り。
		AnimationDaiLanding,//高所からの着地。
		AnimationDownFly,	//吹っ飛び。
		AnimationDamage_00,//ダメージ。
	};

	//プレイヤーの状態遷移の種類。
	enum PlayerState {
		StateInvalid = -1,
		StateWait_00,		//待機(立ち)。
		StateWait_01,		//待機(腕伸ばし)。
		StateWait_02,		//待機(クルクル)。
		StateWalk,          //歩き。
		StateRun,			//走り。
		StateSLID,			//スライディング。
		StateBackStep,		//バックステップ。
		StateFall,			//落下。
		StateLanding,		//着地。
		StateJump,			//ジャンプ。
		StateDamage,		//ダメージを受けている。
		StateDead,			//死んでいる。
		StateAttack,		//攻撃中。
	};

private:
	D3DXVECTOR3		m_position;					//座標。
	D3DXVECTOR3     m_scale;					//スケール。
	D3DXMATRIX		m_world;					//ワールド行列。
	Camera*         m_camera;					//カメラのインスタンス。
	int				m_currentAnimSetNo;			//現在再生しているアニメーション。
	PlayerState     m_state;					//プレイヤーの状態。
	D3DXQUATERNION  m_rotation;					//回転行列。
	D3DXVECTOR3     m_moveDir;					//カメラから求めた方向。
	D3DXVECTOR3     m_move;						//移動量。
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
	bool			m_battleFlag;				//バトル中かのフラグ。
	float			m_fallTimer;				//落下時間。
	int				m_hp;						//ヒットポイント。
	int				m_maxhp;					//最大ヒットポイント。
	D3DXVECTOR3		m_UniDir;					//ユニティちゃんの移動ベクトル(敵の移動処理で使う)。
	float			m_atrTime;					//この時間を超えたら当たりを発生させる。
	int				m_lv;						//プレイヤーのレベル。
	int				m_lvUpEXP;					//レベルアップに必要な経験値。
	int				m_holdEXP;					//プレイヤーが持っている経験値。
	int				m_getEXP;					//敵から取得した経験値。
	CSoundSource	m_soundSource;
	CSoundSource	m_soundSource2;
	long long levelUpExpTable[MAX_LEVEL];
	SParicleEmitParameter m_param;
	std::list<CParticleEmitter*>	m_particleEmitterList;
	Light			m_light;
};
