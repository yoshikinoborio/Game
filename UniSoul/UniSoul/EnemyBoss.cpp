#include "stdafx.h"
#include "EnemyBoss.h"
#include "SceneManager.h"

namespace {
	const DamageCollisionWorld::Collision* dmgColli = NULL;
}

EnemyBoss::EnemyBoss()
{
	m_position = Vector3Zero;
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale =Vector3Zero;
	m_move = Vector3Zero;
	m_height = 0.0f;
	m_radius = 0.0f;
	m_state = EnemyState::enStateSearch;
	m_currentAnimSetNo = EnemyAnimation::enAnimInvalid;
	m_hp = 0;
	m_isDead = FALSE;
	m_unitytyan = g_pScenes->GetUnityChan();
	m_posDifference = Vector3Zero;
	m_isTurn = FALSE;
	m_atrTime = 0.0f;
	m_bossBattleFlag = FALSE;
}


EnemyBoss::~EnemyBoss()
{
	delete m_skinModelData;
}

void EnemyBoss::Initialize(const char* modelPath,const D3DXVECTOR3& pos,const D3DXQUATERNION& rotation,const D3DXVECTOR3& scale)
{
	//モデルのロード。
	m_skinModelData = static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load(modelPath, &m_animation);
	
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

	m_light.SetAmbientLight(D3DXVECTOR4(30.3f, 0.3f, 0.3f, 1.0f));
	m_skinModel.SetLight(&m_light);
	m_skinModel.SetHasNormalMap(FALSE);

	//距離フォグのフラグを設定。
	m_skinModel.SetFogDistFlag(TRUE);
	//距離フォグのパラメーターを設定。
	m_skinModel.SetFogDistParam(150.0f, 300.0f);
	//高さフォグのフラグを設定
	m_skinModel.SetFogHeightFlag(FALSE);

	//アニメーションの設定。
	m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimAttack, FALSE);


	//Unityで出力した情報を元に設定。
	m_position = pos;
	m_rotation = rotation;
	m_scale = scale;

	//半径と高さ。
	m_height = 2.0f;
	m_radius = 1.5f;

	m_hp = 50;
	m_maxhp = m_hp;

	m_state = EnemyState::enStateSearch;

	m_dropEXP =500000;

	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//重力強め。
	
	//各状態での移動スピードを設定。
	this->SetMoveSpeed(0.0f, 0.02f*60.0f, 0.2f*60.0f);
}

void EnemyBoss::Update()
{
	m_animation.Update(GetLocalFrameDeltaTime());

	m_move = m_characterController.GetMoveSpeed();

	//プレイヤーに向かうベクトルの計算。
	m_posDifference = m_unitytyan->GetUnityChanPos() - m_position;

	m_isTurn = FALSE;

	//どこかに発生している当たり判定を探している処理。
	DamageSearch();

	//ボスのワールド行列を取得。
	D3DXMATRIX& BossPos = m_skinModel.GetWorldMatrix();

	//距離判定に使う変数。
	D3DXVECTOR3 PosDiff = m_posDifference;

	switch (m_state)
	{
	case EnemyState::enStateSearch: {
		float selfangle;
		//敵の視野角を作って視野角内にプレイヤーがいるかを調べる。
		selfangle = m_CreateViewAngle.CreateView(PosDiff, BossPos);
		//自分の視野角にいるかつ距離が500以下の時。
		if (selfangle < 50.0f&&D3DXVec3LengthSq(&PosDiff) < 500.0f)
		{
			//発見。
			m_state = EnemyState::enStateFind;
			
			break;
		}
		m_currentAnimSetNo = EnemyAnimation::enAnimWait;
		m_move.x = m_moveSpeed;
		m_move.z = m_moveSpeed;
	}
		break;
	case EnemyState::enStateFind:
	{
		m_bossBattleFlag = TRUE;
		m_moveSpeed = m_runSpeed;
		m_isTurn = TRUE;
		m_posDifference.y = 0.0f;

		D3DXVECTOR3 work = m_posDifference;
		D3DXVECTOR3 dir = Vector3Zero;
		//キャラが向いている方向を正規化。
		D3DXVec3Normalize(&dir, &work);

		//敵をプレイヤーの向きに進ませる。
		m_move = m_moveSpeed * dir;

		//回転の処理。
		if (D3DXVec3Length(&work) > 0.0f)
		{
			D3DXVECTOR3 forward = Vector3Forward;
			//回転量の計算。
			m_targetAngleY = acos(D3DXVec3Dot(&forward, &dir));
			D3DXVECTOR3 axis;
			//ベクトルとベクトルの外積を取って+,-どちらに回すかを決める。
			D3DXVec3Cross(&axis, &forward, &work);
			D3DXVec3Normalize(&axis, &axis);
			
			if (axis.y < 0.0f)
			{
				m_targetAngleY *= -1.0f;
			}
			//向きたい方向と上方向から軸を作りその軸を回転軸としてクォータニオンを回転。
			D3DXQuaternionRotationAxis(&m_rotation, &axis, m_currentAngleY);
		}
		m_currentAnimSetNo = EnemyAnimation::enAnimRun;;
		//索敵範囲内にプレイヤーを発見。
		//発見中に近くに行くと攻撃する。
		if (D3DXVec3LengthSq(&PosDiff) < 10.0f)
		{
			m_state = EnemyState::enStateAttack;
		}
	}
		break;
	case EnemyState::enStateAttack: {
		m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimAttack, TRUE);
		m_atrTime += DeltaTime;
		//攻撃時に当たり判定を生成。
		//ボスの前方向に当たり判定を発生させる。
		if (m_atrTime >= 0.7f)
		{
			g_damageCollisionWorld->Add(1.0f, D3DXVECTOR3(BossPos.m[3][0], BossPos.m[3][1], BossPos.m[3][2]), 1.7f, 20, g_damageCollisionWorld->enDamageToPlayer, 0);
			m_atrTime = 0.0f;

		}
		//攻撃中にプレイヤーが攻撃可能範囲外に移動したら追跡。
		if (D3DXVec3LengthSq(&PosDiff) > 11.0f)
		{
			//攻撃が終わってから移動開始。
			if (!m_animation.IsPlay())
			{
				m_state = EnemyState::enStateFind;
				m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimAttack, FALSE);
				m_moveSpeed = m_runSpeed;
			}

		}
		m_currentAnimSetNo = EnemyAnimation::enAnimAttack;
		//攻撃中は移動しない。
		m_move = Vector3Zero;
	}
		break;
		//ダメージを受けている。
	case EnemyState::enStateDamage: {
		DamageProcess();
	}
		break;
		//死んだ状態。
	case EnemyState::enStateDead: {
		m_moveSpeed = 0.0f;
		//完全に死んだらプレイヤーに経験値を渡す。
		m_unitytyan->AddPlayerEXP(m_dropEXP);
		//エネミーマネージャーに死んだことを伝えるフラグをTRUEにする。
		m_isDead = TRUE;
		//キャラクターコントローラーの解放。
		m_characterController.RemoveRigidBoby();
	}
		break;
	}	

	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_move);
	//キャラクタコントローラーを実行。
	m_characterController.Execute(GetLocalFrameDeltaTime());
	//キャラクターコントロールで計算した位置をエネミーの位置に反映。
	m_position = m_characterController.GetPosition();

	//計算させた回転の反映。
	m_currentAngleY = m_turn.Update(m_isTurn, m_targetAngleY);

	m_animation.PlayAnimation((int)m_currentAnimSetNo, 0.1f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void EnemyBoss::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowCaster)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowCaster);

	//１フレームの経過時間の取得。
	m_frameDeltaTime = static_cast<GameScene*>(g_pScenes)->GetFrameDeltaTime();
}

void EnemyBoss::DamageSearch()
{
	RigidBody* rb = m_characterController.GetRigidBody();
	//どこかに発生している当たり判定を探している。
	dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
		DamageCollisionWorld::enDamageToEnemy,
		rb->GetBody()
	);

	if (dmgColli != NULL)
	{
		m_state = EnemyState::enStateDamage;
		m_bossBattleFlag = TRUE;
	}
}

void EnemyBoss::DamageProcess() 
{
	if (dmgColli != NULL)
	{
		//ダメージを受けて体力を減らした結果0にならなければ体力を引く。
		if (m_hp > 0.0f)
		{
			//ダメージを受けた。
			m_hp -= dmgColli->damage;
		}
		
		if (m_hp <= 0.0f) {
			//死亡
			m_hp = 0;
			m_state = EnemyState::enStateDead;
		}
		else {
			m_state = EnemyState::enStateFind;
		}
	}

	
}
