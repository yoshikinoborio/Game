#include "stdafx.h"
#include "EnemyGoblin.h"
#include "SceneManager.h"

EnemyGoblin::EnemyGoblin()
{
	m_position = Vector3Zero;
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = Vector3Zero;
	m_move = Vector3Zero;
	m_height = 0.0f;
	m_radius = 0.0f;
	m_state = EnemyState::enStateSearch;
	m_currentAnimSetNo = EnemyAnimation::enAnimInvalid;
	m_hp = 0;
	m_isDead = FALSE;
	m_isTurn = FALSE;
	m_unitytyan = g_pScenes->GetUnityChan();
	m_posDifference = Vector3Zero;
}


EnemyGoblin::~EnemyGoblin()
{
	delete m_skinModelData;
}

void EnemyGoblin::Initialize(const char* modelPath, const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale)
{
	//モデルのロード。
	m_skinModelData= static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load(modelPath, &m_animation);
	
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
	m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimAttack, FALSE);
	m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimDamage, FALSE);
	m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimDead, FALSE);
	m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimJump, FALSE);
	m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimLanding, FALSE);

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

	//各状態での移動スピードを設定。
	this->SetMoveSpeed(0.0f, 0.005f*60.0f, 0.05f*60.0f);
}

void EnemyGoblin::Update()
{
	m_animation.Update(GetLocalFrameDeltaTime());

	m_move = m_characterController.GetMoveSpeed();

	//プレイヤーに向かうベクトルの計算。
	m_posDifference = m_unitytyan->GetUnityChanPos() - m_position;

	m_isTurn = FALSE;

	//ゴブリンのワールド行列を取得。
	D3DXMATRIX& GoblinPos = m_skinModel.GetWorldMatrix();

	//距離判定に使う変数。
	D3DXVECTOR3 PosDiff = m_posDifference;

	Damage();

	//ジャンプ中にジャンプさせないための処理。
	//if (m_state==EnemyState::enStateSearch && m_characterController.IsOnGround() == TRUE)
	//{
	//	//ジャンプの初速度。
	//	m_move.y = 10.0f;
	//	m_characterController.Jump();
	//	m_state = EnemyState::enStateJump;
	//}

	switch (m_state)
	{
	case EnemyState::enStateSearch:
		if (m_characterController.IsOnGround() == TRUE)
		{
			float selfangle;
			//敵の視野角を作って視野角内にプレイヤーがいるかを調べる。
			selfangle = m_CreateViewAngle.CreateView(PosDiff, GoblinPos);
			//自分の視野角にいるかつ距離が500以下の時。
			if (selfangle < 50.0f&&D3DXVec3LengthSq(&PosDiff) < 500.0f)
			{
				//発見。
				m_state = EnemyState::enStateFind;
				break;
			}
			m_move.x = m_moveSpeed;
			m_move.z = m_moveSpeed;
		}
		else
		{
			m_state = EnemyState::enStateFall;
		}
		break;
	case EnemyState::enStateFind:
		if (m_characterController.IsOnGround() == TRUE)
		{
			m_moveSpeed = m_runSpeed;
			m_isTurn = TRUE;
			m_posDifference.y = 0.0f;

			//キャラが向いている方向を正規化。
			D3DXVec3Normalize(&m_posDifference, &m_posDifference);

			//敵をプレイヤーの向きに進ませる。
			m_move.x = m_moveSpeed*m_posDifference.x;
			m_move.z = m_moveSpeed*m_posDifference.z;

			//回転の処理。
			if (D3DXVec3Length(&m_posDifference) > 0.0f)
			{
				D3DXVECTOR3 forward = Vector3Forward;
				//回転量の計算。
				m_targetAngleY = acos(D3DXVec3Dot(&forward, &m_posDifference));
				D3DXVECTOR3 axis;
				//ベクトルとベクトルの外積を取って+,-どちらに回すかを決める。
				D3DXVec3Cross(&axis, &forward, &m_posDifference);
				D3DXVec3Normalize(&axis, &axis);

				if (axis.y < 0.0f)
				{
					m_targetAngleY *= 1.0f;
				}
				//向きたい方向と上方向から軸を作りその軸を回転軸としてクォータニオンを回転。
				D3DXQuaternionRotationAxis(&m_rotation, &axis, m_currentAngleY);
			}

			//索敵範囲内にプレイヤーを発見。
			//発見中に近くに行くと攻撃する。
			if (D3DXVec3LengthSq(&PosDiff) < 2.5f)
			{
				m_state = EnemyState::enStateAttack;
			}
		}
		else
		{
			m_state = EnemyState::enStateFall;
		}
		break;
	case EnemyState::enStateAttack:
		m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimAttack, TRUE);
		m_atrTime += DeltaTime;
		//攻撃時に当たり判定を生成。
		//ゴブリンの前方向に当たり判定を発生させる。
		if (m_atrTime >= 0.7f)
		{
			g_damageCollisionWorld->Add(2.0f, D3DXVECTOR3(GoblinPos.m[3][0], GoblinPos.m[3][1], GoblinPos.m[3][2]), 0.005f, 5, g_damageCollisionWorld->enDamageToPlayer, 0);
			m_atrTime = 0.0f;

		}
		//攻撃中にプレイヤーが攻撃可能範囲外に移動したら追跡。
		if (D3DXVec3LengthSq(&PosDiff) > 3.0f)
		{
			//攻撃が終わってから移動開始。
			if (!m_animation.IsPlay())
			{
				m_state = EnemyState::enStateFind;
				m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimAttack, FALSE);
				m_moveSpeed = m_runSpeed;
			}

		}
		//攻撃中は移動しない。
		m_move = Vector3Zero;
		break;
	case EnemyState::enStateJump:
		//ジャンプのアニメーションが終わったら落下に遷移。
		if (!m_animation.IsPlay())
		{
			m_state = EnemyState::enStateFall;
		}
		break;
	case EnemyState::enStateFall:
		//落下中に地面に着地。
		if (m_characterController.IsOnGround() == TRUE)
		{
			//着地に遷移。
			m_state = EnemyState::enStateLanding;
			//着地した。
		}
		else
		{
			//落下中。
			m_state = EnemyState::enStateFall;
		}
		break;
	case EnemyState::enStateLanding:
		if (m_characterController.IsOnGround() == TRUE)
		{
			//着地のアニメーションが終わったら待機かプレイヤーを追跡中にする。
			if (!m_animation.IsPlay()) {
				m_state = EnemyState::enStateSearch;
			}
		}
		else
		{
			m_state = EnemyState::enStateFall;
		}
		break;
	case EnemyState::enStateDamage:
		//ダメージを受けたらプレイヤー発見状態にする。
		if (!m_animation.IsPlay())
		{
			m_state = EnemyState::enStateFind;
		}
		break;
	case EnemyState::enStateDead:
		m_moveSpeed = 0.0f;
		if (!m_animation.IsPlay()) {
			//完全に死んだらプレイヤーに経験値を渡す。
			m_unitytyan->AddPlayerEXP(m_dropEXP);
			//エネミーマネージャーに死んだことを伝えるフラグをTRUEにする。
			m_isDead = TRUE;
			//キャラクターコントロールから解放。
			m_characterController.RemoveRigidBoby();
		}
		break;
	}

	//エネミーの状態を見て再生するアニメーションを設定。
	if (m_state == EnemyState::enStateSearch)
	{
		//止まっていたら待機で動いていたら歩きモーションを設定。
		if (m_moveSpeed > m_waitSpeed)
		{
			//歩きを設定。
			//歩きモーション。
			m_currentAnimSetNo = EnemyAnimation::enAnimWalk;
		}
		else
		{
			//待機を設定。
			//待機モーション。
			m_currentAnimSetNo = EnemyAnimation::enAnimWait;
		}
	}
	//プレイヤーを発見。
	else if (m_state == EnemyState::enStateFind)
	{
		//走りモーション。
		m_currentAnimSetNo = EnemyAnimation::enAnimRun;
	}
	//攻撃を設定。
	else if (m_state == EnemyState::enStateAttack)
	{
		//攻撃モーション。
		m_currentAnimSetNo = EnemyAnimation::enAnimAttack;
	}
	//ダメージ状態を設定。
	else if (m_state == EnemyState::enStateDamage)
	{
		//ダメージモーション。
		m_currentAnimSetNo = EnemyAnimation::enAnimDamage;
	}
	//死状態を設定。
	else if (m_state == EnemyState::enStateDead)
	{
		//死モーション。
		m_currentAnimSetNo = EnemyAnimation::enAnimDead;
	}
	//落下状態。
	else if (m_state == EnemyState::enStateFall)
	{
		//落下モーション。
		m_currentAnimSetNo = EnemyAnimation::enAnimFall;
	}
	//ジャンプ状態。
	else if (m_state == EnemyState::enStateJump)
	{
		//ジャンプアニメーション。
		m_currentAnimSetNo = EnemyAnimation::enAnimJump;
	}
	else if (m_state == EnemyState::enStateLanding)
	{
		m_currentAnimSetNo = EnemyAnimation::enAnimLanding;
	}

	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_move);
	//１フレームの経過時間の取得。
	m_frameDeltaTime = static_cast<GameScene*>(g_pScenes)->GetFrameDeltaTime();
	//キャラクタコントローラーを実行。
	m_characterController.Execute(GetLocalFrameDeltaTime());
	//キャラクターコントロールで計算した位置をエネミーの位置に反映。
	m_position = m_characterController.GetPosition();
	m_position.y += 0.7f;

	//計算させた回転の反映。
	m_currentAngleY = m_turn.Update(m_isTurn, m_targetAngleY);

	m_animation.PlayAnimation((int)m_currentAnimSetNo, 0.1f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void EnemyGoblin::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowReceiver);
}

void EnemyGoblin::Damage()
{
	//死んでいたら何もしない。
	if (m_state == EnemyState::enStateDamage || m_state == EnemyState::enStateDead)
	{
		return;
	}
	RigidBody* rb = m_characterController.GetRigidBody();
	//どこかに発生している当たり判定を探している。
	const DamageCollisionWorld::Collision* dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
		DamageCollisionWorld::enDamageToEnemy,
		rb->GetBody()
	);

	if (dmgColli != NULL)
	{
		//ダメージを受けた。
		m_hp -= dmgColli->damage;
		if (m_hp <= 0.0f) {
			//死亡
			m_hp = 0;
			m_state = EnemyState::enStateDead;
		}
		else {
			m_state = EnemyState::enStateDamage;
		}
	}
}