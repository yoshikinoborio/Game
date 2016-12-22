#include "stdafx.h"
#include "EnemySkeleton.h"
#include "Game.h"

EnemySkeleton::EnemySkeleton()
{
	m_initPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posDifference = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SkeDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = SkeletonStateSearch;
	m_height = 0.0f;
	m_radius = 0.0f;
	m_walkTimer = 0.0f;
	m_hp = 0;
	m_atrTime = 0.0f;
	m_isDead = FALSE;
	m_unitytyan = game->GetUnityChan();
}

EnemySkeleton::~EnemySkeleton()
{
	Release();
}

void EnemySkeleton::Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale)
{
	//オリジナルのモデルからコピー(クローン)を作成。
	m_skinModelData.CloneModelData(g_orginSkinModelData, &m_animation);
	//クローンを使って初期化。
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

	//アニメーションの設定。
	m_animation.SetAnimationLoopFlag(enAnimAttack, FALSE);
	m_animation.SetAnimationLoopFlag(enAnimDamage, FALSE);
	m_animation.SetAnimationLoopFlag(enAnimDead, FALSE);

	//Unityで出力した情報を元に設定。
	m_position = pos;
	m_initPos = m_position;
	this->m_rotation = rotation;
	m_scale = scale;

	//索敵中から開始。
	m_state = SkeletonStateSearch;

	//スケルトンの半径と高さ。
	m_height = 1.0f;
	m_radius = 0.6f;
	

	m_hp = 10;

	m_dropEXP = 100;

	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//重力強め。

	g_damageCollisionWorld = new DamageCollisionWorld;
	g_damageCollisionWorld->Start();
}

void EnemySkeleton::Update()
{
	if (m_isDead != TRUE)
	{
		m_animation.Update(1.0f / 60.0f);

		m_move = m_characterController.GetMoveSpeed();

		m_unityPos = m_unitytyan->GetUnityChanPos();

		m_isTurn = FALSE;

		m_posDifference = m_unityPos - m_position;

		//距離判定に使う変数。
		D3DXVECTOR3 PosDiff = m_posDifference;

		// スケルトンのワールド行列を取得。
		D3DXMATRIX& SkePos = m_skinModel.GetWorldMatrix();

		Damage();

		switch (m_state)
		{
			//索敵中。
		case SkeletonStateSearch:
			//地面に着いている時。
			if (m_characterController.IsOnGround() == TRUE)
			{
				//ユニティちゃんが近くに来た時の処理。
				if (D3DXVec3LengthSq(&PosDiff) < 500.0f)
				{
					//発見。
					m_state = SkeletonStateFind;
					break;
				}
				//近くにいない時は索敵中。
				m_state = SkeletonStateSearch;
				m_moveSpeed = SKELETONWAITTIME;
				//m_moveSpeed = SKELETONWAITTIME;
				SearchMove();
			}
			break;
			//発見。
		case SkeletonStateFind:
			m_moveSpeed = SKELETONRUNSPEED;
			//索敵範囲内にユニティちゃんを発見。
			//発見中に近くに行くと攻撃する。
			if (D3DXVec3LengthSq(&PosDiff) < 10.0f)
			{
				m_state = SkeletonStateAttack;
			}
			FindMove();
			break;
		case SkeletonStateAttack:
			m_animation.SetAnimationLoopFlag(enAnimAttack, TRUE);
			m_atrTime += DeltaTime;
			//攻撃時に当たり判定を生成。
			//スケルトンの前方向に当たり判定を発生させる。
			if (m_atrTime >= 1.2f)
			{
				g_damageCollisionWorld->Add(20.0f, D3DXVECTOR3(SkePos.m[3][0], SkePos.m[3][1], SkePos.m[3][2]), 0.03f, 10, g_damageCollisionWorld->enDamageToPlayer, 0);
				m_atrTime = 0.0f;
			}
			//攻撃中にユニティちゃんが攻撃可能範囲外に移動したら追跡。
			if (D3DXVec3LengthSq(&PosDiff) > 10.0f)
			{
				//攻撃が終わってから移動開始。
				if (!m_animation.IsPlay())
				{
					m_state = SkeletonStateFind;
					m_animation.SetAnimationLoopFlag(enAnimAttack, FALSE);
				}
			}

			//攻撃中は移動しない。
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case SkeletonStateDamage:
			//EnemyBase::PlayAnimationForce(EnemyBase::enAnimDamage);
			if (!m_animation.IsPlay())
			{
				m_state = SkeletonStateFind;
			}
			break;
		case SkeletonStateDead:
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_moveSpeed = 0.0f;
			m_move.y = 10.0f;
			break;
		}

		if (m_state == SkeletonStateSearch)
		{
			if (m_moveSpeed > SKELETONWAITTIME)
			{
				m_currentAnimSetNo = enAnimWalk;
			}
			else
			{
				m_currentAnimSetNo = enAnimWait;
			}
		}
		else if (m_state == SkeletonStateFind)
		{
			m_currentAnimSetNo = enAnimRun;
		}
		else if (m_state == SkeletonStateAttack)
		{
			m_currentAnimSetNo = enAnimAttack;
		}
		else if (m_state == SkeletonStateDamage)
		{
			m_currentAnimSetNo = enAnimDamage;
		}
		else if (m_state == SkeletonStateDead)
		{
			m_currentAnimSetNo = enAnimDead;
			if (!m_animation.IsPlay())
			{
				m_unitytyan->AddPlayerEXP(m_dropEXP);
				m_isDead = TRUE;
				m_characterController.RemoveRigidBoby();
			}
		}

		//キャラクタが動く速度を設定。
		m_characterController.SetMoveSpeed(m_move);
		//キャラクタコントローラーを実行。
		m_characterController.Execute();
		//キャラクターコントロールで計算した位置をエネミーの位置に反映。
		m_position = m_characterController.GetPosition();

		//向きたい方向と上方向から軸を作りその軸を回転軸としてクォータニオンを回転。
		D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_targetAngleY);

		g_damageCollisionWorld->Update();

		m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);

		m_skinModel.Update(m_position, m_rotation, m_scale);
	}
}

void EnemySkeleton::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix,isShadowReceiver);
}

void EnemySkeleton::Release()
{
	m_skinModelData.Release();
}

void EnemySkeleton::FindMove()
{
	m_isTurn = TRUE;

	m_posDifference.y = 0.0f;

	//プレイヤーが移動する先を読み迎撃する処理。
	m_SkeDir = m_posDifference;

	//プレイヤーと敵の相対速度を求める。
	D3DXVECTOR3 Vr = m_unitytyan->GetUniDir() - m_SkeDir;
	//プレイヤーと敵の相対距離を求める。
	D3DXVECTOR3 Sr = m_unitytyan->GetUnityChanPos() - m_position;
	//接近時間を求める。
	D3DXVECTOR3 Tc;
	Tc.x = abs(Sr.x) / abs(Vr.x);
	Tc.y = abs(Sr.y) / abs(Vr.y);
	Tc.z = abs(Sr.z) / abs(Vr.z);

	//迎撃ポイント。
	D3DXVECTOR3 GeigekiPos;
	GeigekiPos.x = m_unitytyan->GetUnityChanPos().x + m_unitytyan->GetUniDir().x * Tc.x;
	GeigekiPos.y = m_unitytyan->GetUnityChanPos().y +m_unitytyan->GetUniDir().y * Tc.y;
	GeigekiPos.y = 0.0f;
	GeigekiPos.z = m_unitytyan->GetUnityChanPos().z + m_unitytyan->GetUniDir().z * Tc.z;

	D3DXVECTOR3 Dir;
	//撃移動量＝||迎撃ポイント－敵座標||×移動量。
	Dir = GeigekiPos - m_position;
	D3DXVec3Normalize(&Dir, &Dir);

	//キャラが向いている方向を正規化。
	D3DXVec3Normalize(&m_posDifference, &m_posDifference);
	
	//敵をユニティちゃんの向きに進ませる。
	//m_movesSpeedに掛ける値をDirにすると先読み型になる。
	m_move.x= m_moveSpeed*m_posDifference.x;
	m_move.z = m_moveSpeed*m_posDifference.z;

	//回転の処理。
	if (D3DXVec3Length(&m_posDifference) > 0.0f)
	{
		D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//回転量の計算。
		m_targetAngleY = acos(D3DXVec3Dot(&forward, &m_posDifference));
		D3DXVECTOR3 axis;
		//ベクトルとベクトルの外積を取って+,-どちらに回すかを決める。
		D3DXVec3Cross(&axis, &forward, &m_posDifference);
		D3DXVec3Normalize(&axis, &axis);
		//負数の時は+にする。
		if (axis.y < 0.0f)
		{
			m_targetAngleY *= -1.0f;
		}
	}
}

void EnemySkeleton::SearchMove()
{
	//m_walkTimer += 1.0f / 60.0f;

}

void EnemySkeleton::Damage()
{
	//死んでいたら何もしない。
	if (m_state == SkeletonStateDamage || m_state == SkeletonStateDead)
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
			m_state = SkeletonStateDead;
		}
		else {
			m_state = SkeletonStateDamage;
		}
	}
}