#pragma once
#include "EnemyBase.h"
#include "CharacterController.h"

class UnityChan;

//エネミーの状態遷移の種類。
enum SkeletonState {
	SkeletonStateWait = 0,	//待機(立ち)。
	SkeletonStateWalk,		//歩き。
	SkeletonStateRun,		//走り。
	SkeletonStateAttack,	//攻撃。
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
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
		bool isShadowReceiver);
	void Release();
private:
	D3DXVECTOR3 m_initPos;						//骨の初期位置。
	SkeletonState     m_state;					//骨の敵の状態。
	CharacterController	m_characterController;	//骨の敵のキャラクタコントローラ。
	float			m_height;					//骨の敵の高さ。
	float			m_radius;					//骨の敵の半径。
	D3DXVECTOR3     m_move;						//移動量。
	UnityChan*		m_unitytyan;				//ユニティちゃんのインスタンス。
	D3DXVECTOR3		m_unityPos;					//ユニティちゃんの位置。
};