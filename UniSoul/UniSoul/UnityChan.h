#pragma once
#include "AnimationModel3D.h"
#include "CharacterController.h"
#include "ParticleEmitter.h"
#include "SoundSource.h"

//このnamespaceを使うとstaticの時に発生する同名との衝突が起きなくなる。そう言う言語の使用。
namespace {
	const float WALKSPEED = 0.02f*60.0f;	//歩くスピード。
	const float RUNSPEED = 0.2f*60.0f;		//走るスピード。
	const float MAX_RUN = 0.6f*60.0f;		//歩きまでの上限値。
	const short MAX_LEVEL = 100;			//レベルの最大値。
											//プレイヤーの配置情報。
	struct PlayerInfo
	{
		D3DXVECTOR3	pos;			//座標。
		D3DXQUATERNION	rotation;	//回転。
	};
};

class CParticleEmitter;
class Camera;


//プレイヤーのクラス。
class UnityChan : public AnimationModel3D
{
public:
	//コンストラクタ。
	UnityChan();

	//デストラクタ。
	~UnityChan();

	//初期化。
	void Initialize();

	//更新。
	void Update()override;

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);

	//パッドによるカメラの奥に移動する処理。
	void PadMove();

	//待機状態での処理。
	void WaitProcess();

	//動いている状態での処理。
	void MoveProcess();

	//ジャンプ状態での処理。
	void JumpProcess();

	//スライディング状態での処理。
	void SLIDProcess();

	//落下状態での処理。
	void FallProcess();

	//着地状態での処理。
	void LandingProcess();

	//バックステップ状態での処理。
	void BackStepProcess();

	//ダメージを受けている状態での処理。
	void DamageProcess();

	//プレイヤーが死んだ状態での処理。
	void DeadProcess();

	//攻撃状態での処理。
	void AttackProcess();

	//マップシフト状態での処理。
	void MapShiftProcess();

	//マップシフトの処理。
	void MapShift();

	//ジャンプ処理。
	void Jump();

	//レベルアップの処理。
	void LevelUp();

	//再生するアニメーションを選択し再生。
	void AnimationSelectPlay();

	//バックステップ。
	void BackStep();

	//敵の攻撃に当たっているかの判定。
	void DamageJudge();

	//プレイヤーのSEの更新。
	void PlayerSEUpdate();

	//キャラクターコントローラーの更新。
	void CharacterControllerUpdate();

	//エネミーの動きを止めるor再開させる処理。
	void EnemyPlayChanger();

	//プレイヤーの位置の取得。
	const D3DXVECTOR3& GetUnityChanPos () const
	{
		return m_position;
	}

	//プレイヤーのワールド行列の取得。
	const D3DXMATRIX& GetUnityChanWorld() const
	{
		return m_world;
	}

	//プレイヤーの大きさの取得。
	const D3DXVECTOR3& GetUnityiChanScale() const
	{
		return m_scale;
	}

	//プレイヤーの回転の取得。
	const D3DXQUATERNION& GetUnityiChanRotation() const
	{
		return m_rotation;
	}

	//プレイヤーの移動ベクトルの取得。
	const D3DXVECTOR3& GetUniDir() const
	{
		return m_UniDir;
	}

	//HPの取得。
	int GetHP() const
	{
		return m_hp;
	}

	//最大HPの取得。
	int GetMaxHP() const
	{
		return m_maxhp;
	}

	//経験値の加算。
	void AddPlayerEXP(int EXP)
	{
		m_getEXP += EXP;
	}

	//プレイヤーのレベルの取得。
	int GetLv() const
	{
		return m_lv;
	}
	
	//ローカル⊿タイムを取得。
	float GetLocalFrameDeltaTime() const
	{
		return  m_frameDeltaTime* m_deltaTimeMul;
	}

	//⊿タイムに乗算される値を設定。
	//グローバル⊿タイムに乗算される値。この値に0.5を設定するとエネミーの挙動が0.5倍速になる。
	void SetFrameDeltaTimeMul(float mul)
	{
		m_deltaTimeMul = mul;
	}

	//プレイヤーで再生されるアニメーションの種類。
	enum PlayerAnimationNo {
		AnimationWait_00 = 0,	//待機(立ち)。
		AnimationWalk,			//歩き。
		AnimationRun,			//走り。
		AnimationWait_01,		//待機(腕伸ばし)。
		AnimationWait_02,		//待機(クルクル)。
		AnimationSLID,			//スライディング。
		AnimationBackStep,		//バックステップ。
		AnimationFall,			//落下中。
		AnimationLanding,		//着地。
		AnimationJump,			//ジャンプ。
		AnimationPunch,			//パンチ。
		AnimationRKick,			//右上段蹴り。
		AnimationRotationKick,	//回し蹴り。
		AnimationSomersault,	//サマーソルト。
		AnimationFightingPause,	//戦闘での待機。
		AnimationFightingRun,	//戦闘での走り。
		AnimationDaiLanding,	//高所からの着地。
		AnimationDownFly,		//吹っ飛び。
		AnimationDamage_00,		//ダメージ。
	};

	//プレイヤーの状態遷移の種類。
	enum PlayerState {
		StateInvalid = -1,
		StateWait,			//待機。
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
		StateMapShift		//マップシフト。
	};

private:
	D3DXVECTOR3		m_position;							//座標。
	D3DXVECTOR3     m_scale;							//スケール。
	D3DXMATRIX		m_world;							//ワールド行列。
	Camera*         m_camera;							//カメラのインスタンス。
	int				m_currentAnimSetNo;					//現在再生しているアニメーション。
	PlayerState     m_state;							//プレイヤーの状態。
	D3DXQUATERNION  m_rotation;							//回転行列。
	D3DXVECTOR3     m_moveDir;							//カメラから求めた方向。
	D3DXVECTOR3     m_move;								//移動量。
	float           m_moveSpeed;						//移動速度(歩く時と走る時の速度調整用)。
	float           m_waitAnimetionChangeTime;			//待機アニメーションの切り替え時間。
	float			m_currentAngleY;					//現在の方向。
	float			m_targetAngleY;						//向きたい方向。
	bool			m_isTurn;							//回転フラグ。
	float           m_saveLStickX;						//左スティックの左右の入力量を格納。
	float			m_saveLStickY;						//左スティックの前後の入力量を格納。
	CharacterController m_characterController;			//キャラクタコントローラ。
	float			m_height;							//プレイヤーの高さ。
	float			m_radius;							//プレイヤーの半径。
	bool			m_battleFlag;						//バトル中かのフラグ。
	float			m_fallTimer;						//落下時間。
	int				m_hp;								//ヒットポイント。
	int				m_maxhp;							//最大ヒットポイント。
	D3DXVECTOR3		m_UniDir;							//プレイヤーの移動ベクトル(敵の移動処理で使う)。
	float			m_atrTime;							//この時間を超えたら当たりを発生させる。
	int				m_lv;								//プレイヤーのレベル。
	int				m_lvUpEXP;							//レベルアップに必要な経験値。
	int				m_holdEXP;							//プレイヤーが持っている経験値。
	int				m_getEXP;							//敵から取得した経験値。
	CSoundSource	m_soundSource;						//着地のSE。
	CSoundSource	m_soundSource2;						//レベルアップのSE。
	long long		m_levelUpExpTable[MAX_LEVEL];		//レベルアップに必要な経験値テーブル。
	CParticleEmitter* m_pEmitter;
	float			m_frameDeltaTime;					//1フレームの経過時間。
	float			m_deltaTimeMul;						//⊿タイムに乗算される値。
	float			m_time;
};
