#include "stdafx.h"
#include "CollisionCreat.h"
#include "SceneManager.h"
#include "CollisionAttr.h"

namespace {
	//見えない当たり判定の配置情報。
	struct CollsionInfo {
		D3DXVECTOR3	pos;			//座標。
		D3DXQUATERNION	rot;	//回転。
		D3DXVECTOR3 scale;			//スケール。
	};
	//見えない当たり判定の配置情報のテーブル。
	CollsionInfo CollsionInfoTable[] = {
#include "CollisionInfo.h"
	};
}

//コンストラクタ。
CollisionCreat::CollisionCreat()
{

}

//デストラクタ。
CollisionCreat::~CollisionCreat()
{
	//ゴーストオブジェクトの削除。
	for (auto ghostobject : m_ghostObjectList)
	{
		delete ghostobject;
	}
}

//初期化。
void CollisionCreat::Initialize()
{
	for (CollsionInfo& CollInfo : CollsionInfoTable) {
		//ゴーストオブジェクトを初期化。

		btBoxShape* box = new btBoxShape(btVector3(CollInfo.scale.x*0.5f, CollInfo.scale.y*0.5f, CollInfo.scale.z*0.5f));

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(CollInfo.pos.x, CollInfo.pos.y, CollInfo.pos.z));
		groundTransform.setRotation(btQuaternion(CollInfo.rot.x, CollInfo.rot.y, CollInfo.rot.z, CollInfo.rot.w));

		//ゴーストオブジェクトの生成。
		btGhostObject* ghost = new btGhostObject();
		ghost->activate();
		//ゴーストオブジェクトの形を箱にする。
		ghost->setCollisionShape(box);

		//各行列の情報をゴーストオブジェクトに設定。
		ghost->setWorldTransform(groundTransform);

		//当たりはリスポーン地点と設定。
		ghost->setUserIndex(enCollisionAttr_Wall);

		//リストに追加。
		m_ghostObjectList.push_back(ghost);

		//物理ワールドに追加。
		static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddGhostObject(ghost);
	}
}