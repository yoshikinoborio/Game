#pragma once
#include <vector>
#include "RigidBody.h"

//コリジョンの配置情報。
struct CollsionInfo {
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
	D3DXVECTOR3 scale;			//スケール。
};

//見えない当たり判定を作成するクラス。
class CollisionCreat
{
public:
	CollisionCreat();
	~CollisionCreat();
	void Initialize();
private:
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	std::vector<btBoxShape*>	m_cllisionShape;	//コリジョン形状。
	RigidBody		m_rigidBody;	//剛体。
};

