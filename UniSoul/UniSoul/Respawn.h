#pragma once
#include "CharacterController.h"

//リスポーンクラス。
class Respawn
{
public:
	//コンストラクタ。
	Respawn();

	//デストラクタ。
	~Respawn();

	//初期化。
	void Initialize();

	//更新。
	void Update();
private:
	CharacterController m_characterController;
	D3DXVECTOR3 		m_position;
	D3DXVECTOR3 		m_size;
	D3DXQUATERNION      m_rotation;
	btBoxShape*			m_GhostShape;	//当たり判定だけがあるコリジョン形状。
	btGhostObject*		m_ghostObject;	//ゴースト。剛体の変わりになるもの。
};

