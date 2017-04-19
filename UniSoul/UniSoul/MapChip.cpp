#include "stdafx.h"
#include "MapChip.h"
#include "SceneManager.h"

//コンストラクタ。
MapChip::MapChip()
{
	m_position = Vector3Zero;
	m_scale = Vector3Zero;
}

//デストラクタ。
MapChip::~MapChip()
{
	delete m_skinModelData;
}

//初期化。
void MapChip::Initialize(const char* modelPath, const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation)
{
	m_position = pos;
	m_scale = Vector3One;
	m_rotation = rotation;

	//モデルをロード。
	m_skinModelData = static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load(modelPath, &m_animation);
	m_skinModel.Initialize(m_skinModelData);

	//ライトの設定。
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	m_skinModel.SetLight(&m_light);

	m_skinModel.SetHasNormalMap(FALSE);

	//距離フォグのフラグを設定。
	m_skinModel.SetFogDistFlag(TRUE);
	//距離フォグのパラメーターを設定。
	m_skinModel.SetFogDistParam(150.0f, 300.0f);
	//高さフォグのフラグを設定。
	m_skinModel.SetFogHeightFlag(FALSE);


	m_skinModel.Update(pos, rotation, m_scale);
	D3DXMATRIX m_world;
	//ここから衝突判定絡みの初期化。
	//スキンモデルからメッシュコライダーを作成する。
	D3DXMATRIX* rootBoneMatrix = m_skinModelData->GetRootBoneWorldMatrix();
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
	static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);
}

//更新。
void MapChip::Update()
{
	//マップオブジェクトを更新。
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

//描画。
void MapChip::Draw(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowCaster)
{
	//マップオブジェクトを描画。
	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowCaster);
}