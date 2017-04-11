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
	m_postion = Vector3Zero;
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

//初期化。
void Respawn::Initialize()
{
	//Unityから出力された情報でをゴーストオブジェクトを生成する処理。
	for (RespawnInfo& respawninfo : RespawnInfoTable)
	{
		//箱を生成。
		btBoxShape* box = new btBoxShape(btVector3(respawninfo.scale.x*0.5f, respawninfo.scale.y*0.5f, respawninfo.scale.z*0.5f));

		//Unityから吐き出された位置、回転、拡大を元に各行列の設定。
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(respawninfo.pos.x, respawninfo.pos.y, respawninfo.pos.z));
		groundTransform.setRotation(btQuaternion(respawninfo.rotation.x, respawninfo.rotation.y, respawninfo.rotation.z, respawninfo.rotation.w));

		//ゴーストオブジェクトの生成。
		btGhostObject* ghost = new btGhostObject();
		ghost->activate();
		//ゴーストオブジェクトの形を箱にする。
		ghost->setCollisionShape(box);

		//各行列の情報をゴーストオブジェクトに設定。
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

	m_pEmitter = CParticleEmitter::EmitterCreate(
		"ParticleEmitterStart",
		ParicleType::Star,
		static_cast<GameScene*>(g_pScenes)->GetFileOperation()->ReadText());
	
}

//更新。
void Respawn::Update()
{
	m_pEmitter->SetEmitPos(static_cast<GameScene*>(g_pScenes)->GetFileOperation()->ReadText());
	m_pEmitter->Update();
}

//描画。
void Respawn::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver) 
{
	m_pEmitter->Render(&viewMatrix, &projMatrix);
}