#include "stdafx.h"
#include "Respawn.h"
#include "CollisionAttr.h"
#include "SceneManager.h"

namespace {
	//リスポーン地点の配置情報。
	struct RespawnInfo {
		D3DXVECTOR3	pos;			//座標。
		D3DXQUATERNION	rotation;	//回転。
		D3DXVECTOR3 scale;			//スケール。
	};

	//リスポーン地点の配置テーブル。
	RespawnInfo RespawnInfoTable[] = {
#include "RespawnInfo.h"
	};
}

//コンストラクタ。
Respawn::Respawn()
{

}

//デストラクタ。
Respawn::~Respawn()
{
	//ゴーストオブジェクトの削除。
	for (auto ghostobject: m_ghostObjectList)
	{
		delete ghostobject;
	}
}

void Respawn::Initialize()
{
	//Unityから出力された情報でをゴーストオブジェクトを生成する処理。
	for (RespawnInfo& respawninfo : RespawnInfoTable)
	{
		//箱を生成。
		btBoxShape* box = new btBoxShape(btVector3(respawninfo.scale.x*0.5f, respawninfo.scale.y*0.5f, respawninfo.scale.z*0.5f));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(respawninfo.pos.x, respawninfo.pos.y, respawninfo.pos.z));
		groundTransform.setRotation(btQuaternion(respawninfo.rotation.x, respawninfo.rotation.y, respawninfo.rotation.z, respawninfo.rotation.w));

		//ゴーストオブジェクトの生成。
		btGhostObject* ghost = new btGhostObject();
		ghost->activate();
		//ゴーストオブジェクトの形を箱にする。
		ghost->setCollisionShape(box);
		ghost->setWorldTransform(groundTransform);

		//ゴーストオブジェクトの位置のアドレスを設定。
		ghost->setUserPointer(&respawninfo.pos);

		//当たりはリスポーン地点と設定。
		ghost->setUserIndex(enCollisionAttr_Respawn);

		//リストに追加。
		m_ghostObjectList.push_back(ghost);

		//物理ワールドに追加。
		static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddGhostObject(ghost);
	}

}

void Respawn::Update()
{

}