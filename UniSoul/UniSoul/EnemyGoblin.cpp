#include "stdafx.h"
#include "EnemyGoblin.h"
#include "SceneManager.h"

EnemyGoblin::EnemyGoblin()
{
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_height = 0.0f;
	m_radius = 0.0f;
	m_state = DragonBoarStateSearch;
	m_currentAnimSetNo = enAnimInvalid;
	m_hp = 0;
	m_isDead = FALSE;
}


EnemyGoblin::~EnemyGoblin()
{
	delete m_skinModelData;
}

void EnemyGoblin::Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale)
{
	//モデルのロード。
	m_skinModelData= static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load(modelPath, &m_animation);
	//m_skinModelData.LoadModelData(modelPath, &m_animation);
	m_skinModel.Initialize(m_skinModelData);

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

	//距離フォグのフラグを設定。
	m_skinModel.SetFogDistFlag(TRUE);
	//距離フォグのパラメーターを設定。
	m_skinModel.SetFogDistParam(150.0f, 300.0f);
	//高さフォグのフラグを設定
	m_skinModel.SetFogHeightFlag(FALSE);

	//アニメーションループの設定。
	//m_animation.SetAnimationLoopFlag(enAnimWait, FALSE);

	//Unityで出力した情報を元に設定。
	m_position = pos;
	this->m_rotation = rotation;
	m_scale = scale;

	//半径と高さ。
	m_height = 1.0f;
	m_radius = 0.8f;

	m_hp = 10;

	m_dropEXP = 100;
	
	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//重力強め。
}

void EnemyGoblin::Update()
{
	m_animation.Update(GetLocalFrameDeltaTime());

	if (m_state == DragonBoarStateSearch)
	{
		m_currentAnimSetNo = enAnimWait;
	}

	m_move = m_characterController.GetMoveSpeed();

	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_move);
	//キャラクタコントローラーを実行。
	m_characterController.Execute(GetLocalFrameDeltaTime());
	//キャラクターコントロールで計算した位置をエネミーの位置に反映。
	m_position = m_characterController.GetPosition();
	m_position.y += 0.7f;

	m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void EnemyGoblin::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowReceiver);
}