#include "stdafx.h"
#include "CollisionCreat.h"
#include "SceneManager.h"
#include "CollisionAttr.h"

//マップチップの配置情報のテーブル。
CollsionInfo CollsionInfoTable[] = {
#include "CollisionInfo.h"
};


CollisionCreat::CollisionCreat()
{
}


CollisionCreat::~CollisionCreat()
{

}

void CollisionCreat::Initialize()
{
	for (CollsionInfo& CollInfo : CollsionInfoTable) {
		//剛体を初期化。
		{
			btBoxShape* work = new btBoxShape(btVector3(CollInfo.scale.x*0.5f, CollInfo.scale.y*0.5f, CollInfo.scale.z*0.5f));
			m_cllisionShape.push_back(work);
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(-CollInfo.pos.x, CollInfo.pos.y, -CollInfo.pos.z));
			groundTransform.setRotation(btQuaternion(-CollInfo.rotation.x, CollInfo.rotation.y, -CollInfo.rotation.z, CollInfo.rotation.w));
			float mass = 0.0f;

			//作成した剛体を物理ワールドに追加。
			static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);

			////続いて剛体を作成する。
			////まずは剛体を作成するための情報を設定。
			//RigidBodyInfo rbInfo;
			//rbInfo.mass = 0.0f;					//質量を0にすると動かない剛体になる。
			//rbInfo.pos = CollInfo.pos;
			//rbInfo.rot = CollInfo.rotation;
			////剛体を作成。
			//m_rigidBody.Create(rbInfo);
			////作成した剛体を物理ワールドに追加。
			//static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);

		}
	}
}