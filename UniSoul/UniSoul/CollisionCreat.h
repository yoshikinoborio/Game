#pragma once
#include <vector>
#include "RigidBody.h"

//見えない当たり判定を作成するクラス。
class CollisionCreat
{
public:
	//コンストラクタ。
	CollisionCreat();

	//デストラクタ。
	~CollisionCreat();

	//初期化。
	void Initialize();
private:
	std::vector<btGhostObject*>		m_ghostObjectList;	//ゴースト。剛体の変わりになるもの。
	//std::vector<RigidBody*>			m_rigidBodyList;	//剛体。
	//RigidBody						m_rigidBody;	//剛体。
};