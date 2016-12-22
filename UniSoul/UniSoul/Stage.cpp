#include "stdafx.h"
#include "Game.h"
#include "Stage.h"

Stage::Stage()
{
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

Stage::~Stage()
{
	Release();
}

//初期化。
void Stage::Initialize()
{
	m_skinModelData.LoadModelData("image\\Ground.X", &m_animation);
	m_skinModel.Initialize(&m_skinModelData);

	//ライトの設定。
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_skinModel.SetLight(&m_light);
	m_skinModel.SetHasNormalMap(FALSE);

	//影描画するフラグをセット
	m_skinModel.SetShadowReceiverFlag(TRUE);
	m_skinModel.Update(m_position, m_rotation, m_scale);
	//ここから衝突判定絡みの初期化。
	//スキンモデルからメッシュコライダーを作成する。
	D3DXMATRIX* rootBoneMatrix = m_skinModelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_skinModel, rootBoneMatrix);
	//続いて剛体を作成する。
	//まずは剛体を作成するための情報を設定。
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;	//剛体のコリジョンを設定する。
	rbInfo.mass = 0.0f;					//質量を0にすると動かない剛体になる。
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	//剛体を作成。
	m_rigidBody.Create(rbInfo);
	//作成した剛体を物理ワールドに追加。
	game->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);
	
}

//更新。
void Stage::Update()
{
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

// 描画。
void Stage::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver){

	m_skinModel.Draw(&viewMatrix, &projMatrix,isShadowReceiver);
}

//開放。
void Stage::Release()
{
	m_skinModelData.Release();
}