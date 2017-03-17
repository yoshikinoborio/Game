#include "stdafx.h"
#include "EnemySkeleton.h"
#include "SceneManager.h"

//コンストラクタ。
EnemySkeleton::EnemySkeleton()
{
	m_initPos = Vector3Zero;
	m_position = Vector3Zero;
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = Vector3Zero;
	m_move = Vector3Zero;
	m_posDifference = Vector3Zero;
	m_SkeDir = Vector3Zero;
	m_state = SkeletonState::StateSearch;
	m_height = 0.0f;
	m_radius = 0.0f;
	m_walkTimer = 0.0f;
	m_hp = 0;
	m_atrTime = 0.0f;
	m_mostNearCourceIndex = 0;
	m_isDead = FALSE;
	m_isTurn = FALSE;
	m_unitytyan = g_pScenes->GetUnityChan();
}

//デストラクタ。
EnemySkeleton::~EnemySkeleton()
{
	delete m_skinModelData;
}

//初期化。
void EnemySkeleton::Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale)
{
	//オリジナルのモデルからコピー(クローン)を作成。
	m_skinModelData = static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load(modelPath, &m_animation);
	//クローンを使って初期化。
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
	m_state = SkeletonState::StateSearch;

	//スケルトンの半径と高さ。
	m_height = 1.0f;
	m_radius = 0.6f;
	
	float Min;
	Min = 99999;	//番兵
	//コース定義の配列の数を計算。
	m_courceArray = sizeof(EnemyCource) / sizeof(EnemyCource[0]);
	for (int i = 0; i < m_courceArray; i++) {
		D3DXVECTOR3 dist;
		dist = m_position - EnemyCource[i];
		float len = D3DXVec3Length(&dist);
		if (len < Min)
		{
			//一番近いコース定義を確保
			m_mostNearCourceIndex = i;
			Min = len;//一番短い長さ
		}
	}

	m_hp = 10;

	m_dropEXP = 100;

	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//重力強め。

}

//更新。
void EnemySkeleton::Update()
{
	if (m_isDead != TRUE)
	{
		m_animation.Update(GetLocalFrameDeltaTime());

		m_move = m_characterController.GetMoveSpeed();

		m_unityPos = m_unitytyan->GetUnityChanPos();

		m_posDifference = m_unityPos - m_position;

		//距離判定に使う変数。
		D3DXVECTOR3 PosDiff = m_posDifference;

		// スケルトンのワールド行列を取得。
		D3DXMATRIX& SkePos = m_skinModel.GetWorldMatrix();

		//ダメージを受ける処理。
		Damage();

		//状態を見て処理の切り替え。
		switch (m_state)
		{
			//索敵中。
		case SkeletonState::StateSearch:
			//地面に着いている時。
			if (m_characterController.IsOnGround() == TRUE)
			{
				m_moveSpeed = SKELETONWAITSPEED;
				//敵の視野角を作って視野角内にプレイヤーがいるかを調べる。
				//自分の向きベクトル。
				D3DXVECTOR3 Dir = D3DXVECTOR3(SkePos.m[3][0], SkePos.m[3][1], SkePos.m[3][2]);
				//プレイヤーへの向きベクトル。
				D3DXVECTOR3 PlayerDir = PosDiff;
				//二つのベクトルを正規化。
				D3DXVec3Normalize(&Dir, &Dir);
				D3DXVec3Normalize(&PlayerDir, &PlayerDir);

				//正規化した二つのベクトルの内積を計算。
				float dot = D3DXVec3Dot(&Dir, &PlayerDir);
				//内積の値の逆余弦からラジアンを求める。
				float rad = acos(dot);
				//ラジアンから角度に変換し実際の角度差を求める。
				float selfangle D3DXToDegree(rad);
				//自分の視野角にいるかつ距離が500以下の時。
				if (selfangle < 50.0f&&D3DXVec3LengthSq(&PosDiff) < 500.0f)
				{
					//発見。
					m_state = SkeletonState::StateFind;
					break;
				}
				//近くにいない時は索敵中。
				SearchMove();
			}
			break;
			//発見。
		case SkeletonState::StateFind:
			m_moveSpeed = SKELETONRUNSPEED;
			FindMove();
			//索敵範囲内にプレイヤーを発見。
			//発見中に近くに行くと攻撃する。
			if (D3DXVec3LengthSq(&PosDiff) < 10.0f)
			{
				m_state = SkeletonState::StateAttack;
			}
			
			if (D3DXVec3LengthSq(&PosDiff) > 500.0f)
			{
				m_state = SkeletonState::StateSearch;
				m_moveSpeed = SKELETONWAITSPEED;
			}
			break;
		case SkeletonState::StateAttack:
			m_animation.SetAnimationLoopFlag(enAnimAttack, TRUE);
			m_atrTime += DeltaTime;
			//攻撃時に当たり判定を生成。
			//スケルトンの前方向に当たり判定を発生させる。
			if (m_atrTime >= 1.3f)
			{
				g_damageCollisionWorld->Add(2.0f, D3DXVECTOR3(SkePos.m[3][0], SkePos.m[3][1], SkePos.m[3][2]), 0.03f, 10, g_damageCollisionWorld->enDamageToPlayer, 0);
				m_atrTime = 0.0f;
				
			}
			//攻撃中にプレイヤーが攻撃可能範囲外に移動したら追跡。
			if (D3DXVec3LengthSq(&PosDiff) > 11.0f)
			{
				//攻撃が終わってから移動開始。
				if (!m_animation.IsPlay())
				{
					m_state = SkeletonState::StateFind;
					m_animation.SetAnimationLoopFlag(enAnimAttack, FALSE);
					m_moveSpeed = SKELETONRUNSPEED;
				}
				
			}
			//攻撃中は移動しない。
			m_move = Vector3Zero;
			break;
		case SkeletonState::StateDamage:
			//ダメージを受けたらプレイヤー発見状態にする。
			if (!m_animation.IsPlay())
			{
				m_state = SkeletonState::StateFind;
			}
			break;
		case SkeletonState::StateDead:
			//m_move = Vector3Zero;
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
		if (m_state == SkeletonState::StateSearch)
		{
			//止まっていたら待機で動いていたら歩きモーションを設定。
			if (m_moveSpeed > SKELETONWAITSPEED)
			{
				//歩きを設定。
				//歩きモーション。
				m_currentAnimSetNo = enAnimWalk;
			}
			else
			{
				//待機を設定。
				//待機モーション。
				m_currentAnimSetNo = enAnimWait;
			}
		}
		//プレイヤーを発見。
		else if (m_state == SkeletonState::StateFind)
		{
			//走りモーション。
			m_currentAnimSetNo = enAnimRun;
		}
		//攻撃を設定。
		else if (m_state == SkeletonState::StateAttack)
		{
			//攻撃モーション。
			m_currentAnimSetNo = enAnimAttack;
		}
		//ダメージ状態を設定。
		else if (m_state == SkeletonState::StateDamage)
		{
			//ダメージモーション。
			m_currentAnimSetNo = enAnimDamage;
		}
		//死状態を設定。
		else if (m_state == SkeletonState::StateDead)
		{
			//死モーション。
			m_currentAnimSetNo = enAnimDead;
		}

		//キャラクタが動く速度を設定。
		m_characterController.SetMoveSpeed(m_move);
		//キャラクタコントローラーを実行。
		m_characterController.Execute(GetLocalFrameDeltaTime());
		//キャラクターコントロールで計算した位置をエネミーの位置に反映。
		m_position = m_characterController.GetPosition();

		//計算させた回転の反映。
		m_currentAngleY = m_turn.Update(m_isTurn, m_targetAngleY);

		m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);

		m_skinModel.Update(m_position, m_rotation, m_scale);
	}
}

//描画。
void EnemySkeleton::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix,isShadowReceiver);
}

//スケルトンが発見状態の時の回転と移動の処理。
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
	
	//敵をプレイヤーの向きに進ませる。
	//m_movesSpeedに掛ける値をDirにすると先読み型になる。
	m_move.x= m_moveSpeed*m_posDifference.x;
	m_move.z = m_moveSpeed*m_posDifference.z;

	//回転の処理。
	if (D3DXVec3Length(&m_posDifference) > 0.0f)
	{
		//回転量の計算。
		m_targetAngleY = acos(D3DXVec3Dot(&Vector3Forward, &m_posDifference));
		D3DXVECTOR3 axis;
		//ベクトルとベクトルの外積を取って+,-どちらに回すかを決める。
		D3DXVec3Cross(&axis, &Vector3Forward, &m_posDifference);
		D3DXVec3Normalize(&axis, &axis);
		
		if (axis.y < 0.0f)
		{
			m_targetAngleY *= 1.0f;
		}
		//向きたい方向と上方向から軸を作りその軸を回転軸としてクォータニオンを回転。
		D3DXQuaternionRotationAxis(&m_rotation, &axis, m_currentAngleY);
	}
}

//スケルトンが索敵中の時の回転と移動の処理。
void EnemySkeleton::SearchMove()
{
	m_state = SkeletonState::StateSearch;

	m_move.x = m_moveSpeed;
	m_move.z = m_moveSpeed;
	//コース定義に従った移動の処理。
	//{
	//	//コース定義に向かうベクトルを求める
	//	D3DXVECTOR3 toCource = EnemyCource[m_mostNearCourceIndex] - m_position;
	//	//コース定義のベクトルの長さを調べる。
	//	float len = D3DXVec3Length(&toCource);
	//	//調べたコース定義のベクトルの長さが10.0f以下なら次のコース定義に進む。
	//	if (len < 10.0f)
	//	{
	//		//コース定義の配列のインデックスを進める。
	//		m_mostNearCourceIndex++;
	//		//最後のコース定義まで来たら一番最初のコース定義に戻る。
	//		if (m_mostNearCourceIndex > m_courceArray)
	//		{
	//			m_mostNearCourceIndex = 0;
	//		}
	//	}
	//	//コース定義に向かうベクトルの正規化。
	//	D3DXVec3Normalize(&toCource, &toCource);

	//	m_move.x = m_moveSpeed*toCource.x;
	//	m_move.z = m_moveSpeed*toCource.z;
	//	//回転。
	//	m_targetAngleY = Turn(toCource);
	//}

}

void EnemySkeleton::Damage()
{
	//死んでいたら何もしない。
	if (/*m_state == SkeletonState::StateDamage ||*/ m_state == SkeletonState::StateDead)
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
			m_state = SkeletonState::StateDead;
		}
		else {
			m_state = SkeletonState::StateDamage;
		}
	}
}