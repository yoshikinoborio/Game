#include "stdafx.h"
#include "UnityChan.h"
#include "DamageCollisionWorld.h"
#include "SceneManager.h"
//�v���C���[�̔z�u���
PlayerInfo PlayerInfoTable= {
		D3DXVECTOR3(114.01f, -5.71f, 397.61f),             //���s�ړ�
		D3DXQUATERNION(0.00f, 0.72f, 0.00f, 0.70f),   //��]
};


UnityChan::UnityChan()
{
	m_state = StateInvalid;
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//D3DXQUATERNION�̈����͉�]��(0.0f�`1.0f��Max);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveSpeed = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_UniDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_height = 0.0f;
	m_radius = 0.0f;
	m_isTurn = FALSE;
	m_battleFlag = FALSE;
	m_fallTimer = 0.0f;
	m_hp = 0;
	m_maxhp = 0;
	m_atrTime = 0.0f;
	m_lv = 0;
	m_lvUpEXP = 0;
	m_holdEXP = 0;
	m_getEXP = 0;
	m_hp = 0;
	m_maxhp = 0;
}

UnityChan::~UnityChan()
{

}

void UnityChan::Initialize()
{
	//���f���̃��[�h�B
	m_skinModelData.LoadModelData("image\\Unitytyan.X", &m_animation);
	m_skinModel.Initialize(&m_skinModelData);

	//���C�g�̐ݒ�B
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_skinModel.SetLight(&m_light);
	//���j�e�B�����̖@���}�b�v�̃��[�h�B
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

	//�A�j���[�V�����ԍ��̏������B
	m_currentAnimSetNo = AnimationWait_00;
	
	//�X�e�[�g�̏������B
	m_state = StateWait_00;

	//��]�����̃N���X�̏������B
	m_turn.Initialize();

	//�J�����̃C���X�^���X�̎擾�B
	m_camera = g_pScenes->GetCamera();

	//���j�e�B�����̍����Ɣ��a�B
	m_height = 1.0f;
	m_radius = 0.5f;

	//�L�����N�^�R���g���[�����������B
	//�����������a�A�������������A��O�������ʒu�B
	m_characterController.Initialize(m_radius, m_height,PlayerInfoTable.pos);
	m_characterController.SetGravity(-20.0f);	//�d�͋��߁B

	//Unity����o�͂����v���C���[�̉�]���ŏ������B
	m_rotation = PlayerInfoTable.rotation;

	//�p�[�e�B�N���̐ݒ�B
	//D3DXMATRIX& UniPos = m_skinModel.GetWorldMatrix();
	m_pEmitter = CParticleEmitter::EmitterCreate(
		"ParticleEmitterStart",
		ParicleType::Star,
		m_position);

	m_lv = 1;
	m_lvUpEXP = 10;
	m_holdEXP = 0;
	m_hp = 100;
	m_maxhp = 100;

	//�o���l�e�[�u���̒��g�̏������B
	int nextLevelPoint = 10;
	levelUpExpTable[0] = 0;
	for (int i = 1; i < 100; i++) {
		nextLevelPoint *= 1.1f;
		levelUpExpTable[i] = levelUpExpTable[i - 1] + nextLevelPoint;
	}
	m_soundSource.Init("image/landing.wav");
	m_soundSource2.Init("image/LvUpSE.wav");
}
void UnityChan::Update()
{
	m_animation.Update(GetLocalFrameDeltaTime());

	//m_pEmitter->Update();

	//�ݐόo���l�ւ̉��Z�B
	m_holdEXP += m_getEXP;
	m_getEXP = 0;
	//�ݐόo���l���K�v�o���l������ƃ��x���A�b�v�B
	while (m_holdEXP >= levelUpExpTable[m_lv] )
	{
		//���x���̉��Z�B
		m_lv += 1;
		m_soundSource2.Play(FALSE);
		m_soundSource2.SetVolume(0.25f);
	}

	//���j�e�B�����̔��a�ƍ�����ݒ�B
	m_characterController.SetRadius(m_radius);
	m_characterController.SetHeight(m_height);

	m_move = m_characterController.GetMoveSpeed();
	
	m_isTurn = FALSE;

	if (m_state!=StateDead)
	{
		if (g_pad.IsTrigger(enButtonX))
		{
			m_state = StateAttack;
		}
	}

	if (g_pad.IsTrigger(enButtonLB1))
	{
		g_enemyManager->SetFrameDeltaTimeMul(0.0f);
	}
	if (g_pad.IsTrigger(enButtonRB1))
	{
		g_enemyManager->SetFrameDeltaTimeMul(1.0f);
	}

	if (g_pad.IsTrigger(enButtonX))
	{
		g_sceneManager->ChangeScene(1);
	}
	
	Damage();

	switch (m_battleFlag)
	{
	case FALSE:
		switch (m_state)
		{//�ҋ@��ԁB
		case StateWait_00:
			if (m_characterController.IsOnGround() == TRUE)
			{
				//�p�b�h�ɂ��J�����̉��Ɉړ����鏈���B
				PadMove();
				//�ړ��ʂ����ē����Ă��邩�~�܂��Ă��邩���`�F�b�N�B
				if (D3DXVec3LengthSq(&m_moveDir) > 0.0001f)
				{
					m_state = StateRun;
				}
				else
				{
					m_state = StateWait_00;
				}

				// �ҋ@����A�{�^���������ƃo�b�N�X�e�b�v�B
				if (g_pad.IsPress(enButtonA))
				{
					//�o�b�N�X�e�b�v�̏����x��ݒ肷�鏈���B
					//�܂����j�e�B�����̃��[���h�s����擾�B
					D3DXMATRIX& UniPos = m_skinModel.GetWorldMatrix();
					//�擾���Ă������[���h�s��̑O�����̋t�����ɑ��x��ݒ�B
					m_move.x = -UniPos.m[2][0] * 15.0f;
					m_move.z = -UniPos.m[2][2] * 15.0f;
					m_state = StateBackStep;

				}

				//B�{�^���������ꂽ��W�����v�B
				Jump();
			}
			else
			{
				m_state = StateFall;
			}
			break;
			//�����Ă����ԁB
		case StateRun:
			StateMove();
			break;
			//�X���C�f�B���O�̏�ԁB
		case StateSLID:
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
					m_state = StateWait_00;
				}
			}
			else
			{
				m_state = StateFall;
			}
			break;
			//�W�����v��ԁB
		case StateJump:
			//�W�����v�̃A�j���[�V�������I������痎���ɑJ�ځB
			if (!m_animation.IsPlay())
			{
				m_state = StateFall;
			}
			//������ԁB
		case StateFall:
			//�������ɒn�ʂɒ��n�B
			if (m_characterController.IsOnGround() == TRUE)
			{
				//���n�ɑJ�ځB
				m_state = StateLanding;
				//���n�����B
				//���n�����Đ��B
				m_soundSource.Play(FALSE);
				m_soundSource.SetVolume(0.25f);
			}
			else
			{
				//�������B
				m_state = StateFall;
				m_fallTimer += 1.0f / 60.0f;
			}
			break;
			//���n��ԁB
		case StateLanding:
			if (m_characterController.IsOnGround() == TRUE)
			{
				PadMove();
				
				//���n���ē����Ă��邩�~�܂��Ă��邩���`�F�b�N�B
				if (D3DXVec3LengthSq(&m_moveDir) > 0.0001f)
				{
					m_state = StateRun;
				}
				else
				{
					//�n�ʂɒ��n���ē��͂�����Ă��Ȃ������璅�n�ɑJ�ځB
					m_state = StateLanding;
					
				}

				//���n�̃A�j���[�V�������I�������ҋ@�ɂ���B
				if (!m_animation.IsPlay()) {
					m_state = StateWait_00;
					//�������Ԃ�0�ɖ߂��B
					m_fallTimer = 0.0f;
				}
			}
			else
			{
				m_state = StateFall;
			}
			break;
			//�o�b�N�X�e�b�v��ԁB
		case StateBackStep:
			if (m_characterController.IsOnGround() == TRUE)
			{
				//�o�b�N�X�e�b�v��A�����������B
				m_move *= 0.96f;
				//�o�b�N�X�e�b�v�̑��x��ݒ�B

				//�o�b�N�X�e�b�v���I��������ҋ@�ɑJ�ځB
				if (!m_animation.IsPlay())
				{
					m_state = StateWait_00;
				}
			}
			else
			{
				m_state = StateFall;
			}
			break;
			//�_���[�W���󂯂Ă����ԁB
		case StateDamage:
			if (!m_animation.IsPlay())
			{
				m_state = StateWait_00;
			}
			PadMove();
			//game->SetSlowFlag(TRUE);
			break;
			//���񂾏�ԁB
		case StateDead:
			//�����Ɏ��񂾎��ɐ�����΂������������\��B
			m_move.y = 10.0f;
			if (!m_animation.IsPlay())
			{
				static_cast<GameScene*>(g_pScenes)->GetYOUDIED()->SetStartFlag(true);
			}
			break;
		case StateAttack:
			m_atrTime += DeltaTime;
			//���j�e�B�����̃��[���h�s����擾�B
			D3DXMATRIX& UniPos = m_skinModel.GetWorldMatrix();
			if (m_atrTime > 0.9f)
			{
				g_damageCollisionWorld->Add(1.5f, D3DXVECTOR3(UniPos.m[3][0], UniPos.m[3][1], UniPos.m[3][2]), 0.05f, 10, DamageCollisionWorld::enDamageToEnemy, 0);
				m_atrTime = 0.0f;
			}
			if (!m_animation.IsPlay())
			{
				m_state = StateWait_00;
			}
			m_move *= 0.89f;
			break;
		}
		break;
	case TRUE:
		break;
	}

	//�v���C���[�̏�Ԃ����čĐ�����A�j���[�V������ݒ�B
	{
		//�ҋ@(����)��ݒ�B
		if (m_state == StateWait_00)
		{
			//�ҋ@(����)�A�j���[�V�����B
			m_currentAnimSetNo = AnimationWait_00;
		}
		else if (m_state == StateWait_00)
		{
			m_currentAnimSetNo = AnimationWait_01;
		}
		else if (m_state == StateWait_02)
		{
			m_currentAnimSetNo = AnimationWait_02;
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
				if (m_fallTimer > 1.0f)
				{
					m_currentAnimSetNo = AnimationDaiLanding;
				}
				else
				{
					m_currentAnimSetNo = AnimationLanding;
				}
			}

			//�W�����v���B
			if (m_state == StateJump)
			{
				//�W�����v�̃A�j���[�V�����B
				m_currentAnimSetNo = AnimationJump;
			}

			if (m_state == StateDamage)
			{
				m_currentAnimSetNo = AnimationDamage_00;
			}

			if (m_state==StateDead)
			{
				m_currentAnimSetNo = AnimationDownFly;
			}

			if (m_state==StateAttack)
			{
				m_currentAnimSetNo = AnimationPunch;
			}
		}
	}

	//�L�����N�^���������x��ݒ�B
	m_characterController.SetMoveSpeed(m_move);
	//�L�����N�^�R���g���[���[�����s�B
	m_characterController.Execute(GetLocalFrameDeltaTime());
	//�L�����N�^�[�R���g���[���Ōv�Z�����ʒu���v���C���[�̈ʒu�ɔ��f�B
	m_position = m_characterController.GetPosition();

	m_soundSource.Update();
	m_soundSource2.Update();

	//g_damageCollisionWorld->Update();

	m_currentAngleY = m_turn.Update(m_isTurn, m_targetAngleY);

	m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void UnityChan::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	//m_pEmitter->Render(&viewMatrix, &projMatrix);
	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowReceiver);
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
	D3DXMATRIX& ViewInv = m_camera->GetViewMatrixInv();//�J�����̋t�s����擾�B
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
	if (D3DXVec3Length(&m_moveDir) > 0.0f)
	{
		D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
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

void UnityChan::Jump()
{
	//B�{�^���������ꂽ��W�����v�B
	if (g_pad.IsPress(enButtonB))
	{
		//�W�����v���ɃW�����v�����Ȃ����߂̏����B
		if (!m_characterController.IsJump()) {
			//�W�����v�̏����x�B
			m_move.y = 10.0f;
			m_characterController.Jump();
			m_state = StateJump;
		}
	}
}

void UnityChan::StateMove()
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
			m_state = StateWait_00;
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
		m_state = StateFall;
	}
}

void UnityChan::Damage()
{
	if (m_state == StateDamage || m_state == StateDead)
	{
		return;
	}

	RigidBody* rb = m_characterController.GetRigidBody();
	//�ǂ����ɔ������Ă��铖���蔻���T���Ă���B
	const DamageCollisionWorld::Collision* dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
		DamageCollisionWorld::enDamageToPlayer,
		rb->GetBody()
		);

	//HP����_���[�W�������炷�B
	if (dmgColli != NULL)
	{
		m_hp -= dmgColli->damage;
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
}