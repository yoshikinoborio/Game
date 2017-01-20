#pragma once
#include "EnemyBase.h"
#include "CharacterController.h"
#include "Light.h"

#define SKELETONWAITTIME 0.0f
#define SKELETONWALKSPEED 0.02f*60.0f
#define SKELETONRUNSPEED 0.2f*60.0f

class UnityChan;

//エネミーの状態遷移の種類。
enum SkeletonState {
	SkeletonStateSearch = 0,//索敵中。
	SkeletonStateFind,		//発見。
	SkeletonStateAttack,	//攻撃。
	SkeletonStateDamage,	//ダメージを受けている。
	SkeletonStateDead,		//死。
};

//エネミー(スケルトン)クラス。
class EnemySkeleton : public EnemyBase
{
public:
	EnemySkeleton();
	~EnemySkeleton();
	void Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale);
	void Update()override;
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
	//スケルトンが発見状態の時の回転と移動の処理。
	void FindMove();
	//スケルトンが索敵中の時の回転と移動の処理。
	void SearchMove();
	//ダメージを受ける処理。
	void Damage();
	//死んだかどうかのフラグを取得。
	bool GetDead()
	{
		return m_isDead;
	}
private:
	D3DXVECTOR3 m_initPos;						//骨の初期位置。
	SkeletonState     m_state;					//骨の敵の状態。
	CharacterController	m_characterController;	//骨の敵のキャラクタコントローラ。
	D3DXVECTOR3     m_move;						//移動量。
	UnityChan*		m_unitytyan;				//ユニティちゃんのインスタンス。
	D3DXVECTOR3		m_unityPos;					//ユニティちゃんの位置。
	D3DXVECTOR3		m_posDifference;			//ユニティちゃんとの距離。
	D3DXVECTOR3		m_SkeDir;					//敵の向きベクトル。
	float			m_walkTimer;				//歩く時間。
	int				m_hp;						//ヒットポイント。
	int				m_dropEXP;					//倒された時に落とす経験値量。
	float			m_atrTime;					//この時間以上になったら当たりを発生させる。
	bool			m_isDead;					//死んだ。
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//コリジョンオブジェクト。
	Light			m_light;
};