#include "stdafx.h"
#include "UnityChan.h"
#include "DamageCollisionWorld.h"
#include "SceneManager.h"


namespace {
	//プレイヤーの配置情報
	PlayerInfo PlayerInfoTable = {
#include "PlayerInfo.h"
	};
	const DamageCollisionWorld::Collision* dmgColli = NULL;
}


UnityChan::UnityChan()
{
	m_state = StateInvalid;
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//D3DXQUATERNIONの引数は回転軸(0.0f～1.0fがMax);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = Vector3Zero;
	m_moveDir =  Vector3Zero;
	m_moveSpeed = 0.0f;
	m_move = Vector3Zero;
	m_UniDir = Vector3Zero;
	m_height = 0.0f;
	m_radius = 0.0f;
	m_isTurn = FALSE;
	m_battleFlag = FALSE;
	m_fallDeltaTime = 0.0f;
	m_hp = 0;
	m_maxhp = 0;
	m_atrTime = 0.0f;
	m_lv = 0;
	m_lvUpEXP = 0;
	m_holdEXP = 0;
	m_getEXP = 0;
	m_hp = 0;
	m_maxhp = 0;
	m_landingTime = 0.0f;
	m_lvUpFlag = FALSE;
}

UnityChan::~UnityChan()
{
	delete m_skinModelData;
}

void UnityChan::Initialize()
{
	//モデルのロード。
	m_skinModelData = static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load("image\\Unitytyan.X", &m_animation);
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
	//プレイヤーの法線マップのロード。
	m_skinModel.LoadNormalMap("image\\body_01_NRM.tga","Plane001");
	m_skinModel.LoadNormalMap("image\\hair_01_NRM.tga","tail");
	m_skinModel.SetHasNormalMap(TRUE);

	//距離フォグのフラグを設定。
	m_skinModel.SetFogDistFlag(FALSE);
	//高さフォグのフラグを設定。
	m_skinModel.SetFogHeightFlag(FALSE);

	//アニメーションの終了時間の設定。
	m_animation.SetAnimationEndtime(AnimationRun, 0.84f);
	m_animation.SetAnimationEndtime(AnimationSLID, 1.5f);
	m_animation.SetAnimationEndtime(AnimationBackStep, 1.0f);
	m_animation.SetAnimationEndtime(AnimationFightingRun, 0.5f);
	m_animation.SetAnimationEndtime(AnimationPunch, 0.5f);
	m_animation.SetAnimationEndtime(AnimationRKick, 0.5f);
	
	//アニメーションのループ設定。
	m_animation.SetAnimationLoopFlag(AnimationSLID,FALSE);
	m_animation.SetAnimationLoopFlag(AnimationBackStep, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationWait_01, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationWait_02, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationLanding, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationJump, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationPunch, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationRKick, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationRotationKick, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationSomersault, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationDaiLanding, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationDownFly, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationDamage_00,FALSE);
	m_animation.SetAnimationLoopFlag(AnimationWin, FALSE);

	//アニメーション番号の初期化。
	m_currentAnimSetNo = AnimationWait_00;
	
	//ステートの初期化。
	m_state = StateWait;

	//回転処理のクラスの初期化。
	m_turn.Initialize();

	//カメラのインスタンスの取得。
	m_camera = g_pScenes->GetCamera();

	//プレイヤーの高さと半径。
	m_height = 1.0f;
	m_radius = 0.5f;
	//デバッグ時の処理。
#ifdef _DEBUG
	//キャラクタコントローラを初期化。
	//第一引数が半径、第二引数が高さ、第三引数が位置。
	m_characterController.Initialize(m_radius, m_height,PlayerInfoTable.pos);
	m_characterController.SetGravity(-20.0f);	//重力強め。
#endif // DEBUG

	//リリース時の処理。
#ifndef _DEBUG
	m_position = static_cast<GameScene*>(g_pScenes)->GetFileOperation()->ReadText();
	m_position = D3DXVECTOR3(67.5f, 3.31f, 76.42f);
	//m_position.x = m_position.x + 3.0f;
	//キャラクタコントローラを初期化。
	//第一引数が半径、第二引数が高さ、第三引数が位置。
	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//重力強め。
#endif // !_DEBUG

	//Unityから出力したプレイヤーの回転情報で初期化。
	m_rotation = PlayerInfoTable.rotation;

	//パーティクルの設定。
	//D3DXMATRIX& UniPos = m_skinModel.GetWorldMatrix();
	//m_pEmitter = CParticleEmitter::EmitterCreate(
	//	"ParticleEmitterStart",
	//	ParicleType::Star,
	//	m_position);

	m_lv = 1;
	m_lvUpEXP = 10;
	m_holdEXP = 0;
	m_hp = 100;
	m_maxhp = m_hp;

	//経験値テーブルの中身の初期化。
	int nextLevelPoint = 10;
	m_levelUpExpTable[0] = 0;
	for (int i = 1; i < MAX_LEVEL; i++) {
		nextLevelPoint *= 1.1f;
		m_levelUpExpTable[i] = m_levelUpExpTable[i - 1] + nextLevelPoint;
	}
	//SEの初期化。
	//オンメモリ再生。
	m_landingSe.Init("image/landing.wav");
	m_lvUpSe.Init("image/UniSoulLvUpSE.wav");

	//ユニティちゃんを進む方向に向けるための処理。
	m_rotation = D3DXQUATERNION(0.0f, 0.06f, 0.0f, 0.998f);

}
void UnityChan::Update()
{
	m_animation.Update(GetLocalFrameDeltaTime());

	//m_pEmitter->Update();

	//プレイヤーの半径と高さを設定。
	m_characterController.SetRadius(m_radius);
	m_characterController.SetHeight(m_height);

	//計算された移動速度を取得。
	m_move = m_characterController.GetMoveSpeed();


	//レベルアップの処理。
	LevelUp();

	if (m_lvUpSe.GetIsPlaying()==TRUE)
	{
		m_lvUpFlag = TRUE;
	}
	else
	{
		m_lvUpFlag = FALSE;
	}

	m_isTurn = FALSE;

	if (m_state != StateWinWait&&m_state != StateWin&&g_enemyManager->GetBoss().GetIsDead() == TRUE)
	{
		m_state = StateWin;
	}

	if (static_cast<GameScene*>(g_pScenes)->GetCamera()->GetCameraFreeFlag() == FALSE)
	{

		if (m_state != StateDead)
		{
			if (g_pad.IsTrigger(enButtonX))
			{
				m_state = StateAttack;
			}
		}

		//エネミーの動きを止めるor再開。
		EnemyPlayChanger();

		//敵の攻撃に当たっているかの判定。
		DamageJudge();

		switch (m_state)
		{//待機状態。
		case StateWait:
			//待機中の処理。
			WaitProcess();
			break;
			//動いている状態。
		case StateRun:
			//動いている状態での処理。。
			MoveProcess();
			break;
			//スライディングの状態。
		case StateSLID:
			//スライディング状態での処理。
			SLIDProcess();
			break;
			//ジャンプ状態。
		case StateJump:
			//ジャンプ状態の処理。
			JumpProcess();
			//落下状態。
		case StateFall:
			//落下状態での処理。
			FallProcess();
			break;
			//着地状態。
		case StateLanding:
			//着地状態での処理。
			LandingProcess();
			break;
			//バックステップ状態。
		case StateBackStep:
			//バックステップ状態での処理。
			BackStepProcess();
			break;
			//ダメージを受けている状態。
		case StateDamage:
			//ダメージを受けている状態での処理。
			DamageProcess();
			break;
			//死んだ状態。
		case StateDead:
			//死んだ状態での処理。
			DeadProcess();
			break;
			//攻撃状態。
		case StateAttack:
			//攻撃状態での処理。
			AttackProcess();
			//勝利時の状態。
			break;
		case StateWin:
			//勝利時の処理。
			WinProcess();
			break;
			//勝利して待機している状態。
		case StateWinWait:
			//勝利して待機している間の処理。
			WinWaitProcess();
			break;
		}
	}

	//再生するアニメーションを選択し再生。
	AnimationSelectPlay();

	//SEの更新。
	PlayerSEUpdate();

	//速度設定、キャラクターコントローラーの実行、計算した位置をプレイヤーに反映。
	CharacterControllerUpdate();

	//計算させた回転の反映。
	m_currentAngleY = m_turn.Update(m_isTurn, m_targetAngleY);

	//位置、回転、大きさをモデルに反映。
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void UnityChan::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowCaster)
{
	//m_pEmitter->Render(&viewMatrix, &projMatrix);
	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowCaster);

	//１フレームの経過時間の取得。
	m_frameDeltaTime = static_cast<GameScene*>(g_pScenes)->GetFrameDeltaTime();
	
}

void UnityChan::LevelUp()
{
	//累積経験値への加算。
	m_holdEXP += m_getEXP;
	m_getEXP = 0;
	//累積経験値が必要経験値を上回るとレベルアップ。
	while (m_holdEXP >= m_levelUpExpTable[m_lv])
	{
		//レベルの加算。
		//レベルが100を超えたらレベルの加算は行わない。
		if (m_lv < MAX_LEVEL)
		{
			m_lv += 1;
			//レベルアップをしているフラグをTRUEにする。
			m_lvUpFlag = TRUE;
		}
		//レベルアップの音。
		m_lvUpSe.Play(FALSE);
		m_lvUpSe.SetVolume(0.4f);
	}
}


void UnityChan::PadMove()
{
	//カメラの方向にプレイヤーを進める処理。
	//左スティックからのカメラ行列における入力を保持。
	//前後の動き
	if (fabs(g_pad.GetLStickXF()) > 0.0f)
	{
		m_isTurn = true;
	}

	//左右の動き
	if (fabsf(g_pad.GetLStickYF()) > 0.0f)
	{
		m_isTurn = true;
	}

	D3DXVECTOR3 moveDirCameraLocal;
	moveDirCameraLocal.y = 0.0f;
	moveDirCameraLocal.x = g_pad.GetLStickXF();
	moveDirCameraLocal.z = g_pad.GetLStickYF();
	D3DXMATRIX ViewInv = m_camera->GetViewMatrixInv();//カメラの逆行列を取得。
	//カメラ空間から見た奥方向のベクトルを取得。
	D3DXVECTOR3 cameraZ;
	cameraZ.x = ViewInv.m[2][0];
	cameraZ.y = 0.0f;		//Y軸いらない。
	cameraZ.z = ViewInv.m[2][2];
	D3DXVec3Normalize(&cameraZ, &cameraZ);	//Y軸を打ち消しているので正規化する。
	//カメラから見た横方向のベクトルを取得。
	D3DXVECTOR3 cameraX;
	cameraX.x = ViewInv.m[0][0];
	cameraX.y = 0.0f;		//Y軸はいらない。
	cameraX.z = ViewInv.m[0][2];
	D3DXVec3Normalize(&cameraX, &cameraX);	//Y軸を打ち消しているので正規化する。

	m_moveDir.x = cameraX.x * moveDirCameraLocal.x + cameraZ.x * moveDirCameraLocal.z;
	m_moveDir.y = 0.0f;	//Y軸はいらない。
	m_moveDir.z = cameraX.z * moveDirCameraLocal.x + cameraZ.z * moveDirCameraLocal.z;

	m_UniDir = m_moveDir;

	m_move.x = m_moveDir.x*m_moveSpeed;
	m_move.z = m_moveDir.z*m_moveSpeed;

	//カメラが向いている方向を正規化。
	D3DXVec3Normalize(&m_moveDir, &m_moveDir);

	//回転の処理。
	if (D3DXVec3Length(&m_UniDir) > 0.0f)
	{
		D3DXVECTOR3 forward = Vector3Forward;
		m_targetAngleY = acos(D3DXVec3Dot(&forward, &m_moveDir));
		D3DXVECTOR3 axis;
		D3DXVec3Cross(&axis, &forward, &m_moveDir);
		if (axis.x > 0.0f)
		{
			m_targetAngleY *= -1.0f;
		}
		//向きたい方向と上方向から軸を作りその軸を回転軸としてクォータニオンを回転。
		D3DXQuaternionRotationAxis(&m_rotation, &axis, m_currentAngleY);
	}
}

void UnityChan::WaitProcess()
{
	if (m_characterController.IsOnGround() == TRUE)
	{
		//パッドによるカメラの奥に移動する処理。
		if (m_camera->GetCameraFreeFlag() != TRUE)
		{
			PadMove();
		}

		//移動量を見て動いているか止まっているかをチェック。
		if (D3DXVec3LengthSq(&m_moveDir) > 0.0001f)
		{
			m_state = StateRun;
		}
		else
		{
			m_state = StateWait;
		}
		//Bボタンを押されたらジャンプ。
		Jump();
		// 待機中にAボタンを押すとバックステップ。
		BackStep();
	}
	else
	{
		CheckFallTime();
	}
}


void UnityChan::MoveProcess()
{
	if (m_characterController.IsOnGround() == TRUE)
	{
		PadMove();
		//移動量を見て動いているか止まっているかをチェック。
		if (D3DXVec3LengthSq(&m_moveDir) > 0.0001f)
		{
			m_state = StateRun;
		}
		else
		{
			m_state = StateWait;
		}

		//入力された値から移動量を求めて一定値を越えたら走りに遷移する。
		if (D3DXVec3LengthSq(&m_move) > 0.6f)
		{
			//走り状態。
			m_state = StateRun;

			//走る時のスピード。
			m_moveSpeed = RUNSPEED;

			//走っている途中にAボタンが押されるとスライディング。
			if (g_pad.IsTrigger(enButtonA))
			{
				m_state = StateSLID;

			}
		}
		else
		{
			//歩く時のスピード。
			m_moveSpeed = WALKSPEED;
		}

		//Bボタンを押されたらジャンプ。
		Jump();
	}
	else
	{
		CheckFallTime();
	}
}

void UnityChan::SLIDProcess()
{
	if (m_characterController.IsOnGround() == TRUE)
	{
		//ちょうど体が傾いてるタイミングで半径と高さを変更。
		double AnimTime = m_animation.GetlocalAnimationTime();
		if (AnimTime > 0.5f)
		{
			//m_characterController.SetRadius(0.5f);
			//m_characterController.SetHeight(0.3f);
		}

		//スライディンが終了したら待機に遷移。
		if (!m_animation.IsPlay())
		{
			m_state = StateWait;
		}
	}
	else
	{
		CheckFallTime();
	}
}

void UnityChan::JumpProcess()
{
	
	//ジャンプのアニメーションが終わったら落下に遷移。
	if (!m_animation.IsPlay())
	{
		m_state = StateFall;
	}
}

void UnityChan::FallProcess()
{
	PadMove();
	//落下中に地面に着地。
	if (m_characterController.IsOnGround() == TRUE)
	{
		//着地に遷移。
		m_state = StateLanding;
		//着地した。
		//着地音を再生。
		m_landingSe.Play(FALSE);
		m_landingSe.SetVolume(0.25f);
	}
	else
	{
		//落下中。
		m_state = StateFall;
		m_landingTime += 1.0f / 60.0f;
	}
}

void UnityChan::LandingProcess()
{

	if (m_characterController.IsOnGround() == TRUE)
	{
		PadMove();

		//着地して動いているか止まっているかをチェック。
		if (D3DXVec3LengthSq(&m_moveDir) > 0.0001f)
		{
			m_state = StateRun;

			m_landingTime = 0.0f;
			//落下時間の初期化。
			m_fallDeltaTime = 0.0f;
		}
		else
		{
			//地面に着地して入力をされていなかったら着地に遷移。
			m_state = StateLanding;
			//落下時間の初期化。
			m_fallDeltaTime = 0.0f;

		}

		//着地のアニメーションが終わったら待機にする。
		if (!m_animation.IsPlay()) {
			m_state = StateWait;
		}
	}
	else
	{
		CheckFallTime();
	}
}

void UnityChan::BackStepProcess()
{
	if (m_characterController.IsOnGround() == TRUE)
	{
		//バックステップ後、少しずつ減速。
		m_move *= 0.96f;

		//バックステップが終了したら待機に遷移。
		if (!m_animation.IsPlay())
		{
			m_state = StateWait;
		}
	}
	else
	{
		CheckFallTime();
	}
}

void UnityChan::DamageProcess()
{
	//HPからダメージ分を減らす。
	if (dmgColli != NULL)
	{
		//ダメージを受けて体力を減らした結果0にならなければ体力を引く。
		if (m_hp > 0.0f)
		{
			//ダメージを受けた。
			m_hp -= dmgColli->damage;
		}

		//ダメージを食らってHPが0になれば死ぬ。
		if (m_hp <= 0.0f) {
			m_hp = 0;
			m_state = StateDead;
		}
		else
		{
			
			m_state = StateDamage;
		}
	}
	if (!m_animation.IsPlay())
	{
		m_state = StateWait;
	}
	PadMove();
}

void UnityChan::DeadProcess()
{
	//ここに死んだ時に吹っ飛ばす処理を書く予定。
	m_move.y = 10.0f;
	if (!m_animation.IsPlay())
	{
		m_isDead = TRUE;
		m_characterController.RemoveRigidBoby();
		m_moveSpeed = 0.0f;
	}
}

void UnityChan::AttackProcess()
{
	m_atrTime += DeltaTime;
	//プレイヤーのワールド行列を取得。
	D3DXMATRIX& UniPos = m_skinModel.GetWorldMatrix();
	if (m_atrTime > 0.9f)
	{
		g_damageCollisionWorld->Add(1.5f, D3DXVECTOR3(UniPos.m[3][0], UniPos.m[3][1], UniPos.m[3][2]), 0.5f, 10, DamageCollisionWorld::enDamageToEnemy, 0);
		m_atrTime = 0.0f;
	}
	if (!m_animation.IsPlay())
	{
		m_state = StateWait;
	}
	m_move *= 0.89f;
}

void UnityChan::DamageJudge()
{
	if (m_state == StateDamage || m_state == StateDead)
	{
		return;
	}
	else
	{
		RigidBody* rb = m_characterController.GetRigidBody();
		//どこかに発生している当たり判定を探している。
		dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
			DamageCollisionWorld::enDamageToPlayer,
			rb->GetBody()
		);

		//当たり判定に当たった。
		if (dmgColli != NULL)
		{
			//ダメージを受ける状態に遷移。
			m_state = StateDamage;
		}
	}	
}

void UnityChan::BackStep()
{
	if (g_pad.IsPress(enButtonA))
	{
		//バックステップの初速度を設定する処理。
		//まずプレイヤーのワールド行列を取得。
		D3DXMATRIX& UniPos = m_skinModel.GetWorldMatrix();
		//取得してきたワールド行列の前方向の逆方向に速度を設定。
		m_move.x = -UniPos.m[2][0] * 15.0f;
		m_move.z = -UniPos.m[2][2] * 15.0f;
		m_state = StateBackStep;
	}
}

void UnityChan::Jump()
{
	//Bボタンを押されたらジャンプ。
	if (g_pad.IsPress(enButtonB))
	{
		//ジャンプの初速度。
		m_move.y = 10.0f;
		m_characterController.Jump();
		m_state = StateJump;
	}
}

void UnityChan::AnimationSelectPlay()
{
	//プレイヤーの状態を見て再生するアニメーションを設定。
	//待機(立ち)を設定。
	if (m_state == StateWait)
	{
		//ランダム関数の初期化。
		srand((unsigned int)time(NULL));
		int RandNum = rand() % 100;
		//1/3の確率で三種類の待機アニメーションが流れる。
		if (0 < RandNum&&RandNum < 33)
		{
			//待機(立ち)アニメーション。
			m_currentAnimSetNo = AnimationWait_00;
		}
		else if (34 < RandNum&&RandNum < 66)
		{
			//待機(腕伸ばし)アニメーション。
			m_currentAnimSetNo = AnimationWait_01;
		}
		else if (67 < RandNum&&RandNum < 100)
		{
			//待機(クルクル)アニメーション。
			m_currentAnimSetNo = AnimationWait_02;
		}
		
	}
	else if (m_state == StateBackStep)
	{
		m_currentAnimSetNo = AnimationBackStep;
	}
	else
	{
		if (m_state == StateRun)
		{
			//動くスピードを見て走りか歩きかを決める。
			if (D3DXVec3LengthSq(&m_characterController.GetMoveSpeed()) > 32.0f)
			{
				//走りを設定。
				//走りのアニメーション。
				m_currentAnimSetNo = AnimationRun;
			}
			else
			{
				//歩きを設定。
				//歩きのアニメーション。
				m_currentAnimSetNo = AnimationWalk;
			}
		}

		//スライディングを設定。
		if (m_state == StateSLID)
		{
			//スライディングのアニメーション。
			m_currentAnimSetNo = AnimationSLID;
		}

		//落下中を設定。
		if (m_state == StateFall)
		{
			//落下中のアニメーション。
			m_currentAnimSetNo = AnimationFall;
		}

		//着地中。
		if (m_state == StateLanding)
		{
			if (m_landingTime > 0.8f)
			{
				//ダイナミックな着地。
				m_currentAnimSetNo = AnimationDaiLanding;
			}
			else
			{
				//普通の着地。
				m_currentAnimSetNo = AnimationLanding;
			}
		}

		//ジャンプ中。
		if (m_state == StateJump)
		{
			//ジャンプのアニメーション。
			m_currentAnimSetNo = AnimationJump;
		}

		//ダメージを受けている。
		if (m_state == StateDamage)
		{
			//ダメージのアニメーション。
			m_currentAnimSetNo = AnimationDamage_00;
		}
		//死んでいる
		if (m_state == StateDead)
		{
			//倒れるアニメーション。
			m_currentAnimSetNo = AnimationDownFly;
		}

		//攻撃している。
		if (m_state == StateAttack)
		{
			//攻撃アニメーション。
			m_currentAnimSetNo = AnimationPunch;
		}

		if (m_state == StateWin)
		{
			m_currentAnimSetNo = AnimationWin;
		}

		if (m_state == StateWinWait)
		{
			m_currentAnimSetNo = AnimationWinWait;
		}
	}
	//アニメーションの再生。
	m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);
}

void UnityChan::PlayerSEUpdate()
{
	//着地、レベルアップのSEの更新。
	m_landingSe.Update();
	m_lvUpSe.Update();
}

void UnityChan::CharacterControllerUpdate()
{
	
	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_move);
	//キャラクタコントローラーを実行。
	m_characterController.Execute(GetLocalFrameDeltaTime());
	//キャラクターコントロールで計算した位置をプレイヤーの位置に反映。
	m_position = m_characterController.GetPosition();
	
}

void UnityChan::EnemyPlayChanger()
{
	if (g_pad.IsTrigger(enButtonLB1))
	{
		//エネミーの動きが止まる。
		g_enemyManager->SetFrameDeltaTimeMul(0.0f);
	}
	if (g_pad.IsTrigger(enButtonRB1))
	{
		//止まっていたエネミーの動きを再開。
		g_enemyManager->SetFrameDeltaTimeMul(1.0f);
	}
}

void UnityChan::WinProcess()
{
	//勝利したアニメーションが終わったら勝利待機中のアニメーションに切り替える。
	if (!m_animation.IsPlay())
	{
		m_state = StateWinWait;
	}
	m_move.x = 0.0f;
	m_move.z = 0.0f;
}

void UnityChan::WinWaitProcess()
{
	//画面を暗くしていくフラグをTRUEにする。
	static_cast<GameScene*>(g_pScenes)->GetBlack()->SetStartFlag(TRUE);

	m_move.x = 0.0f;
	m_move.z = 0.0f;
	
}

//落下している時間を加算し一定値を超えたら落下状態にする。
void UnityChan::CheckFallTime()
{
	//落下している時間を加算。
	m_fallDeltaTime += 1.0f / 60.0f;
	float FallTime = 0.9f;
	//ある値を超えたら落下状態にする。
	if (m_fallDeltaTime > FallTime)
	{
		m_state = StateFall;
	}
}