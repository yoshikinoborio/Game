#include "stdafx.h"
#include "UnityChan.h"
#include "DamageCollisionWorld.h"
#include "SceneManager.h"


namespace {
	//�v���C���[�̔z�u���
	PlayerInfo PlayerInfoTable = {
#include "PlayerInfo.h"
	};
	const DamageCollisionWorld::Collision* dmgColli = NULL;
}


UnityChan::UnityChan()
{
	m_state = StateInvalid;
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//D3DXQUATERNION�̈����͉�]��(0.0f�`1.0f��Max);
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
	//���f���̃��[�h�B
	m_skinModelData = static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load("image\\Unitytyan.X", &m_animation);
	m_skinModel.Initialize(m_skinModelData);

	//���C�g�̐ݒ�B
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
	//�v���C���[�̖@���}�b�v�̃��[�h�B
	m_skinModel.LoadNormalMap("image\\body_01_NRM.tga","Plane001");
	m_skinModel.LoadNormalMap("image\\hair_01_NRM.tga","tail");
	m_skinModel.SetHasNormalMap(TRUE);

	//�����t�H�O�̃t���O��ݒ�B
	m_skinModel.SetFogDistFlag(FALSE);
	//�����t�H�O�̃t���O��ݒ�B
	m_skinModel.SetFogHeightFlag(FALSE);

	//�A�j���[�V�����̏I�����Ԃ̐ݒ�B
	m_animation.SetAnimationEndtime(AnimationRun, 0.84f);
	m_animation.SetAnimationEndtime(AnimationSLID, 1.5f);
	m_animation.SetAnimationEndtime(AnimationBackStep, 1.0f);
	m_animation.SetAnimationEndtime(AnimationFightingRun, 0.5f);
	m_animation.SetAnimationEndtime(AnimationPunch, 0.5f);
	m_animation.SetAnimationEndtime(AnimationRKick, 0.5f);
	
	//�A�j���[�V�����̃��[�v�ݒ�B
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

	//�A�j���[�V�����ԍ��̏������B
	m_currentAnimSetNo = AnimationWait_00;
	
	//�X�e�[�g�̏������B
	m_state = StateWait;

	//��]�����̃N���X�̏������B
	m_turn.Initialize();

	//�J�����̃C���X�^���X�̎擾�B
	m_camera = g_pScenes->GetCamera();

	//�v���C���[�̍����Ɣ��a�B
	m_height = 1.0f;
	m_radius = 0.5f;
	//�f�o�b�O���̏����B
#ifdef _DEBUG
	//�L�����N�^�R���g���[�����������B
	//�����������a�A�������������A��O�������ʒu�B
	m_characterController.Initialize(m_radius, m_height,PlayerInfoTable.pos);
	m_characterController.SetGravity(-20.0f);	//�d�͋��߁B
#endif // DEBUG

	//�����[�X���̏����B
#ifndef _DEBUG
	m_position = static_cast<GameScene*>(g_pScenes)->GetFileOperation()->ReadText();
	m_position = D3DXVECTOR3(67.5f, 3.31f, 76.42f);
	//m_position.x = m_position.x + 3.0f;
	//�L�����N�^�R���g���[�����������B
	//�����������a�A�������������A��O�������ʒu�B
	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//�d�͋��߁B
#endif // !_DEBUG

	//Unity����o�͂����v���C���[�̉�]���ŏ������B
	m_rotation = PlayerInfoTable.rotation;

	//�p�[�e�B�N���̐ݒ�B
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

	//�o���l�e�[�u���̒��g�̏������B
	int nextLevelPoint = 10;
	m_levelUpExpTable[0] = 0;
	for (int i = 1; i < MAX_LEVEL; i++) {
		nextLevelPoint *= 1.1f;
		m_levelUpExpTable[i] = m_levelUpExpTable[i - 1] + nextLevelPoint;
	}
	//SE�̏������B
	//�I���������Đ��B
	m_landingSe.Init("image/landing.wav");
	m_lvUpSe.Init("image/UniSoulLvUpSE.wav");

	//���j�e�B������i�ޕ����Ɍ����邽�߂̏����B
	m_rotation = D3DXQUATERNION(0.0f, 0.06f, 0.0f, 0.998f);

}
void UnityChan::Update()
{
	m_animation.Update(GetLocalFrameDeltaTime());

	//m_pEmitter->Update();

	//�v���C���[�̔��a�ƍ�����ݒ�B
	m_characterController.SetRadius(m_radius);
	m_characterController.SetHeight(m_height);

	//�v�Z���ꂽ�ړ����x���擾�B
	m_move = m_characterController.GetMoveSpeed();


	//���x���A�b�v�̏����B
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

		//�G�l�~�[�̓������~�߂�or�ĊJ�B
		EnemyPlayChanger();

		//�G�̍U���ɓ������Ă��邩�̔���B
		DamageJudge();

		switch (m_state)
		{//�ҋ@��ԁB
		case StateWait:
			//�ҋ@���̏����B
			WaitProcess();
			break;
			//�����Ă����ԁB
		case StateRun:
			//�����Ă����Ԃł̏����B�B
			MoveProcess();
			break;
			//�X���C�f�B���O�̏�ԁB
		case StateSLID:
			//�X���C�f�B���O��Ԃł̏����B
			SLIDProcess();
			break;
			//�W�����v��ԁB
		case StateJump:
			//�W�����v��Ԃ̏����B
			JumpProcess();
			//������ԁB
		case StateFall:
			//������Ԃł̏����B
			FallProcess();
			break;
			//���n��ԁB
		case StateLanding:
			//���n��Ԃł̏����B
			LandingProcess();
			break;
			//�o�b�N�X�e�b�v��ԁB
		case StateBackStep:
			//�o�b�N�X�e�b�v��Ԃł̏����B
			BackStepProcess();
			break;
			//�_���[�W���󂯂Ă����ԁB
		case StateDamage:
			//�_���[�W���󂯂Ă����Ԃł̏����B
			DamageProcess();
			break;
			//���񂾏�ԁB
		case StateDead:
			//���񂾏�Ԃł̏����B
			DeadProcess();
			break;
			//�U����ԁB
		case StateAttack:
			//�U����Ԃł̏����B
			AttackProcess();
			//�������̏�ԁB
			break;
		case StateWin:
			//�������̏����B
			WinProcess();
			break;
			//�������đҋ@���Ă����ԁB
		case StateWinWait:
			//�������đҋ@���Ă���Ԃ̏����B
			WinWaitProcess();
			break;
		}
	}

	//�Đ�����A�j���[�V������I�����Đ��B
	AnimationSelectPlay();

	//SE�̍X�V�B
	PlayerSEUpdate();

	//���x�ݒ�A�L�����N�^�[�R���g���[���[�̎��s�A�v�Z�����ʒu���v���C���[�ɔ��f�B
	CharacterControllerUpdate();

	//�v�Z��������]�̔��f�B
	m_currentAngleY = m_turn.Update(m_isTurn, m_targetAngleY);

	//�ʒu�A��]�A�傫�������f���ɔ��f�B
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void UnityChan::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowCaster)
{
	//m_pEmitter->Render(&viewMatrix, &projMatrix);
	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowCaster);

	//�P�t���[���̌o�ߎ��Ԃ̎擾�B
	m_frameDeltaTime = static_cast<GameScene*>(g_pScenes)->GetFrameDeltaTime();
	
}

void UnityChan::LevelUp()
{
	//�ݐόo���l�ւ̉��Z�B
	m_holdEXP += m_getEXP;
	m_getEXP = 0;
	//�ݐόo���l���K�v�o���l������ƃ��x���A�b�v�B
	while (m_holdEXP >= m_levelUpExpTable[m_lv])
	{
		//���x���̉��Z�B
		//���x����100�𒴂����烌�x���̉��Z�͍s��Ȃ��B
		if (m_lv < MAX_LEVEL)
		{
			m_lv += 1;
			//���x���A�b�v�����Ă���t���O��TRUE�ɂ���B
			m_lvUpFlag = TRUE;
		}
		//���x���A�b�v�̉��B
		m_lvUpSe.Play(FALSE);
		m_lvUpSe.SetVolume(0.4f);
	}
}


void UnityChan::PadMove()
{
	//�J�����̕����Ƀv���C���[��i�߂鏈���B
	//���X�e�B�b�N����̃J�����s��ɂ�������͂�ێ��B
	//�O��̓���
	if (fabs(g_pad.GetLStickXF()) > 0.0f)
	{
		m_isTurn = true;
	}

	//���E�̓���
	if (fabsf(g_pad.GetLStickYF()) > 0.0f)
	{
		m_isTurn = true;
	}

	D3DXVECTOR3 moveDirCameraLocal;
	moveDirCameraLocal.y = 0.0f;
	moveDirCameraLocal.x = g_pad.GetLStickXF();
	moveDirCameraLocal.z = g_pad.GetLStickYF();
	D3DXMATRIX ViewInv = m_camera->GetViewMatrixInv();//�J�����̋t�s����擾�B
	//�J������Ԃ��猩���������̃x�N�g�����擾�B
	D3DXVECTOR3 cameraZ;
	cameraZ.x = ViewInv.m[2][0];
	cameraZ.y = 0.0f;		//Y������Ȃ��B
	cameraZ.z = ViewInv.m[2][2];
	D3DXVec3Normalize(&cameraZ, &cameraZ);	//Y����ł������Ă���̂Ő��K������B
	//�J�������猩���������̃x�N�g�����擾�B
	D3DXVECTOR3 cameraX;
	cameraX.x = ViewInv.m[0][0];
	cameraX.y = 0.0f;		//Y���͂���Ȃ��B
	cameraX.z = ViewInv.m[0][2];
	D3DXVec3Normalize(&cameraX, &cameraX);	//Y����ł������Ă���̂Ő��K������B

	m_moveDir.x = cameraX.x * moveDirCameraLocal.x + cameraZ.x * moveDirCameraLocal.z;
	m_moveDir.y = 0.0f;	//Y���͂���Ȃ��B
	m_moveDir.z = cameraX.z * moveDirCameraLocal.x + cameraZ.z * moveDirCameraLocal.z;

	m_UniDir = m_moveDir;

	m_move.x = m_moveDir.x*m_moveSpeed;
	m_move.z = m_moveDir.z*m_moveSpeed;

	//�J�����������Ă�������𐳋K���B
	D3DXVec3Normalize(&m_moveDir, &m_moveDir);

	//��]�̏����B
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
		//�������������Ə�������玲����肻�̎�����]���Ƃ��ăN�H�[�^�j�I������]�B
		D3DXQuaternionRotationAxis(&m_rotation, &axis, m_currentAngleY);
	}
}

void UnityChan::WaitProcess()
{
	if (m_characterController.IsOnGround() == TRUE)
	{
		//�p�b�h�ɂ��J�����̉��Ɉړ����鏈���B
		if (m_camera->GetCameraFreeFlag() != TRUE)
		{
			PadMove();
		}

		//�ړ��ʂ����ē����Ă��邩�~�܂��Ă��邩���`�F�b�N�B
		if (D3DXVec3LengthSq(&m_moveDir) > 0.0001f)
		{
			m_state = StateRun;
		}
		else
		{
			m_state = StateWait;
		}
		//B�{�^���������ꂽ��W�����v�B
		Jump();
		// �ҋ@����A�{�^���������ƃo�b�N�X�e�b�v�B
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
		//�ړ��ʂ����ē����Ă��邩�~�܂��Ă��邩���`�F�b�N�B
		if (D3DXVec3LengthSq(&m_moveDir) > 0.0001f)
		{
			m_state = StateRun;
		}
		else
		{
			m_state = StateWait;
		}

		//���͂��ꂽ�l����ړ��ʂ����߂Ĉ��l���z�����瑖��ɑJ�ڂ���B
		if (D3DXVec3LengthSq(&m_move) > 0.6f)
		{
			//�����ԁB
			m_state = StateRun;

			//���鎞�̃X�s�[�h�B
			m_moveSpeed = RUNSPEED;

			//�����Ă���r����A�{�^�����������ƃX���C�f�B���O�B
			if (g_pad.IsTrigger(enButtonA))
			{
				m_state = StateSLID;

			}
		}
		else
		{
			//�������̃X�s�[�h�B
			m_moveSpeed = WALKSPEED;
		}

		//B�{�^���������ꂽ��W�����v�B
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
		//���傤�Ǒ̂��X���Ă�^�C�~���O�Ŕ��a�ƍ�����ύX�B
		double AnimTime = m_animation.GetlocalAnimationTime();
		if (AnimTime > 0.5f)
		{
			//m_characterController.SetRadius(0.5f);
			//m_characterController.SetHeight(0.3f);
		}

		//�X���C�f�B�����I��������ҋ@�ɑJ�ځB
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
	
	//�W�����v�̃A�j���[�V�������I������痎���ɑJ�ځB
	if (!m_animation.IsPlay())
	{
		m_state = StateFall;
	}
}

void UnityChan::FallProcess()
{
	PadMove();
	//�������ɒn�ʂɒ��n�B
	if (m_characterController.IsOnGround() == TRUE)
	{
		//���n�ɑJ�ځB
		m_state = StateLanding;
		//���n�����B
		//���n�����Đ��B
		m_landingSe.Play(FALSE);
		m_landingSe.SetVolume(0.25f);
	}
	else
	{
		//�������B
		m_state = StateFall;
		m_landingTime += 1.0f / 60.0f;
	}
}

void UnityChan::LandingProcess()
{

	if (m_characterController.IsOnGround() == TRUE)
	{
		PadMove();

		//���n���ē����Ă��邩�~�܂��Ă��邩���`�F�b�N�B
		if (D3DXVec3LengthSq(&m_moveDir) > 0.0001f)
		{
			m_state = StateRun;

			m_landingTime = 0.0f;
			//�������Ԃ̏������B
			m_fallDeltaTime = 0.0f;
		}
		else
		{
			//�n�ʂɒ��n���ē��͂�����Ă��Ȃ������璅�n�ɑJ�ځB
			m_state = StateLanding;
			//�������Ԃ̏������B
			m_fallDeltaTime = 0.0f;

		}

		//���n�̃A�j���[�V�������I�������ҋ@�ɂ���B
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
		//�o�b�N�X�e�b�v��A�����������B
		m_move *= 0.96f;

		//�o�b�N�X�e�b�v���I��������ҋ@�ɑJ�ځB
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
	//HP����_���[�W�������炷�B
	if (dmgColli != NULL)
	{
		//�_���[�W���󂯂đ̗͂����炵������0�ɂȂ�Ȃ���Α̗͂������B
		if (m_hp > 0.0f)
		{
			//�_���[�W���󂯂��B
			m_hp -= dmgColli->damage;
		}

		//�_���[�W��H�����HP��0�ɂȂ�Ύ��ʁB
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
	//�����Ɏ��񂾎��ɐ�����΂������������\��B
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
	//�v���C���[�̃��[���h�s����擾�B
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
		//�ǂ����ɔ������Ă��铖���蔻���T���Ă���B
		dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
			DamageCollisionWorld::enDamageToPlayer,
			rb->GetBody()
		);

		//�����蔻��ɓ��������B
		if (dmgColli != NULL)
		{
			//�_���[�W���󂯂��ԂɑJ�ځB
			m_state = StateDamage;
		}
	}	
}

void UnityChan::BackStep()
{
	if (g_pad.IsPress(enButtonA))
	{
		//�o�b�N�X�e�b�v�̏����x��ݒ肷�鏈���B
		//�܂��v���C���[�̃��[���h�s����擾�B
		D3DXMATRIX& UniPos = m_skinModel.GetWorldMatrix();
		//�擾���Ă������[���h�s��̑O�����̋t�����ɑ��x��ݒ�B
		m_move.x = -UniPos.m[2][0] * 15.0f;
		m_move.z = -UniPos.m[2][2] * 15.0f;
		m_state = StateBackStep;
	}
}

void UnityChan::Jump()
{
	//B�{�^���������ꂽ��W�����v�B
	if (g_pad.IsPress(enButtonB))
	{
		//�W�����v�̏����x�B
		m_move.y = 10.0f;
		m_characterController.Jump();
		m_state = StateJump;
	}
}

void UnityChan::AnimationSelectPlay()
{
	//�v���C���[�̏�Ԃ����čĐ�����A�j���[�V������ݒ�B
	//�ҋ@(����)��ݒ�B
	if (m_state == StateWait)
	{
		//�����_���֐��̏������B
		srand((unsigned int)time(NULL));
		int RandNum = rand() % 100;
		//1/3�̊m���ŎO��ނ̑ҋ@�A�j���[�V�����������B
		if (0 < RandNum&&RandNum < 33)
		{
			//�ҋ@(����)�A�j���[�V�����B
			m_currentAnimSetNo = AnimationWait_00;
		}
		else if (34 < RandNum&&RandNum < 66)
		{
			//�ҋ@(�r�L�΂�)�A�j���[�V�����B
			m_currentAnimSetNo = AnimationWait_01;
		}
		else if (67 < RandNum&&RandNum < 100)
		{
			//�ҋ@(�N���N��)�A�j���[�V�����B
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
			//�����X�s�[�h�����đ��肩�����������߂�B
			if (D3DXVec3LengthSq(&m_characterController.GetMoveSpeed()) > 32.0f)
			{
				//�����ݒ�B
				//����̃A�j���[�V�����B
				m_currentAnimSetNo = AnimationRun;
			}
			else
			{
				//������ݒ�B
				//�����̃A�j���[�V�����B
				m_currentAnimSetNo = AnimationWalk;
			}
		}

		//�X���C�f�B���O��ݒ�B
		if (m_state == StateSLID)
		{
			//�X���C�f�B���O�̃A�j���[�V�����B
			m_currentAnimSetNo = AnimationSLID;
		}

		//��������ݒ�B
		if (m_state == StateFall)
		{
			//�������̃A�j���[�V�����B
			m_currentAnimSetNo = AnimationFall;
		}

		//���n���B
		if (m_state == StateLanding)
		{
			if (m_landingTime > 0.8f)
			{
				//�_�C�i�~�b�N�Ȓ��n�B
				m_currentAnimSetNo = AnimationDaiLanding;
			}
			else
			{
				//���ʂ̒��n�B
				m_currentAnimSetNo = AnimationLanding;
			}
		}

		//�W�����v���B
		if (m_state == StateJump)
		{
			//�W�����v�̃A�j���[�V�����B
			m_currentAnimSetNo = AnimationJump;
		}

		//�_���[�W���󂯂Ă���B
		if (m_state == StateDamage)
		{
			//�_���[�W�̃A�j���[�V�����B
			m_currentAnimSetNo = AnimationDamage_00;
		}
		//����ł���
		if (m_state == StateDead)
		{
			//�|���A�j���[�V�����B
			m_currentAnimSetNo = AnimationDownFly;
		}

		//�U�����Ă���B
		if (m_state == StateAttack)
		{
			//�U���A�j���[�V�����B
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
	//�A�j���[�V�����̍Đ��B
	m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);
}

void UnityChan::PlayerSEUpdate()
{
	//���n�A���x���A�b�v��SE�̍X�V�B
	m_landingSe.Update();
	m_lvUpSe.Update();
}

void UnityChan::CharacterControllerUpdate()
{
	
	//�L�����N�^���������x��ݒ�B
	m_characterController.SetMoveSpeed(m_move);
	//�L�����N�^�R���g���[���[�����s�B
	m_characterController.Execute(GetLocalFrameDeltaTime());
	//�L�����N�^�[�R���g���[���Ōv�Z�����ʒu���v���C���[�̈ʒu�ɔ��f�B
	m_position = m_characterController.GetPosition();
	
}

void UnityChan::EnemyPlayChanger()
{
	if (g_pad.IsTrigger(enButtonLB1))
	{
		//�G�l�~�[�̓������~�܂�B
		g_enemyManager->SetFrameDeltaTimeMul(0.0f);
	}
	if (g_pad.IsTrigger(enButtonRB1))
	{
		//�~�܂��Ă����G�l�~�[�̓������ĊJ�B
		g_enemyManager->SetFrameDeltaTimeMul(1.0f);
	}
}

void UnityChan::WinProcess()
{
	//���������A�j���[�V�������I������珟���ҋ@���̃A�j���[�V�����ɐ؂�ւ���B
	if (!m_animation.IsPlay())
	{
		m_state = StateWinWait;
	}
	m_move.x = 0.0f;
	m_move.z = 0.0f;
}

void UnityChan::WinWaitProcess()
{
	//��ʂ��Â����Ă����t���O��TRUE�ɂ���B
	static_cast<GameScene*>(g_pScenes)->GetBlack()->SetStartFlag(TRUE);

	m_move.x = 0.0f;
	m_move.z = 0.0f;
	
}

//�������Ă��鎞�Ԃ����Z�����l�𒴂����痎����Ԃɂ���B
void UnityChan::CheckFallTime()
{
	//�������Ă��鎞�Ԃ����Z�B
	m_fallDeltaTime += 1.0f / 60.0f;
	float FallTime = 0.9f;
	//����l�𒴂����痎����Ԃɂ���B
	if (m_fallDeltaTime > FallTime)
	{
		m_state = StateFall;
	}
}