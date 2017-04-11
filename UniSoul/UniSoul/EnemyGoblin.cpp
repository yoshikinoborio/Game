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
	m_state = EnemyGoblinState::StateSearch;
	m_currentAnimSetNo = enAnimInvalid;
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
	//���f���̃��[�h�B
	m_skinModelData= static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load(modelPath, &m_animation);
	
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
	m_skinModel.SetHasNormalMap(FALSE);

	//�����t�H�O�̃t���O��ݒ�B
	m_skinModel.SetFogDistFlag(TRUE);
	//�����t�H�O�̃p�����[�^�[��ݒ�B
	m_skinModel.SetFogDistParam(150.0f, 300.0f);
	//�����t�H�O�̃t���O��ݒ�
	m_skinModel.SetFogHeightFlag(FALSE);

	//�A�j���[�V�������[�v�̐ݒ�B
	m_animation.SetAnimationLoopFlag(enAnimAttack, FALSE);
	m_animation.SetAnimationLoopFlag(enAnimDamage, FALSE);
	m_animation.SetAnimationLoopFlag(enAnimDead, FALSE);
	m_animation.SetAnimationLoopFlag(enAnimJump, FALSE);
	m_animation.SetAnimationLoopFlag(enAnimLanding, FALSE);

	//Unity�ŏo�͂����������ɐݒ�B
	m_position = pos;
	this->m_rotation = rotation;
	m_scale = scale;

	//���a�ƍ����B
	m_height = 1.0f;
	m_radius = 0.8f;

	m_hp = 10;

	m_dropEXP = 100;
	
	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//�d�͋��߁B
}

void EnemyGoblin::Update()
{
	m_animation.Update(GetLocalFrameDeltaTime());

	m_move = m_characterController.GetMoveSpeed();

	//�v���C���[�Ɍ������x�N�g���̌v�Z�B
	m_posDifference = m_unitytyan->GetUnityChanPos() - m_position;

	m_isTurn = FALSE;

	//�S�u�����̃��[���h�s����擾�B
	D3DXMATRIX& GoblinPos = m_skinModel.GetWorldMatrix();

	//��������Ɏg���ϐ��B
	D3DXVECTOR3 PosDiff = m_posDifference;

	Damage();

	//�W�����v���ɃW�����v�����Ȃ����߂̏����B
	//if (m_state==EnemyGoblinState::StateSearch && m_characterController.IsOnGround() == TRUE)
	//{
	//	//�W�����v�̏����x�B
	//	m_move.y = 10.0f;
	//	m_characterController.Jump();
	//	m_state = EnemyGoblinState::StateJump;
	//}

	switch (m_state)
	{
	case EnemyGoblinState::StateSearch:
		if (m_characterController.IsOnGround() == TRUE)
		{
			float selfangle;
			//�G�̎���p������Ď���p���Ƀv���C���[�����邩�𒲂ׂ�B
			selfangle = m_CreateViewAngle.CreateView(PosDiff, GoblinPos);
			//�����̎���p�ɂ��邩������500�ȉ��̎��B
			if (selfangle < 50.0f&&D3DXVec3LengthSq(&PosDiff) < 500.0f)
			{
				//�����B
				m_state = EnemyGoblinState::StateFind;
				break;
			}
			m_move.x = m_moveSpeed;
			m_move.z = m_moveSpeed;
		}
		else
		{
			m_state = EnemyGoblinState::StateFall;
		}
		break;
	case EnemyGoblinState::StateFind:
		if (m_characterController.IsOnGround() == TRUE)
		{
			m_moveSpeed = GOBLINRUNSPEED;
			m_isTurn = TRUE;
			m_posDifference.y = 0.0f;

			//�L�����������Ă�������𐳋K���B
			D3DXVec3Normalize(&m_posDifference, &m_posDifference);

			//�G���v���C���[�̌����ɐi�܂���B
			m_move.x = m_moveSpeed*m_posDifference.x;
			m_move.z = m_moveSpeed*m_posDifference.z;

			//��]�̏����B
			if (D3DXVec3Length(&m_posDifference) > 0.0f)
			{
				D3DXVECTOR3 forward = Vector3Forward;
				//��]�ʂ̌v�Z�B
				m_targetAngleY = acos(D3DXVec3Dot(&forward, &m_posDifference));
				D3DXVECTOR3 axis;
				//�x�N�g���ƃx�N�g���̊O�ς������+,-�ǂ���ɉ񂷂������߂�B
				D3DXVec3Cross(&axis, &forward, &m_posDifference);
				D3DXVec3Normalize(&axis, &axis);

				if (axis.y < 0.0f)
				{
					m_targetAngleY *= 1.0f;
				}
				//�������������Ə�������玲����肻�̎�����]���Ƃ��ăN�H�[�^�j�I������]�B
				D3DXQuaternionRotationAxis(&m_rotation, &axis, m_currentAngleY);
			}

			//���G�͈͓��Ƀv���C���[�𔭌��B
			//�������ɋ߂��ɍs���ƍU������B
			if (D3DXVec3LengthSq(&PosDiff) < 2.5f)
			{
				m_state = EnemyGoblinState::StateAttack;
			}
		}
		else
		{
			m_state = EnemyGoblinState::StateFall;
		}
		break;
	case EnemyGoblinState::StateAttack:
		m_animation.SetAnimationLoopFlag(enAnimAttack, TRUE);
		m_atrTime += DeltaTime;
		//�U�����ɓ����蔻��𐶐��B
		//�S�u�����̑O�����ɓ����蔻��𔭐�������B
		if (m_atrTime >= 0.7f)
		{
			g_damageCollisionWorld->Add(2.0f, D3DXVECTOR3(GoblinPos.m[3][0], GoblinPos.m[3][1], GoblinPos.m[3][2]), 0.005f, 5, g_damageCollisionWorld->enDamageToPlayer, 0);
			m_atrTime = 0.0f;

		}
		//�U�����Ƀv���C���[���U���\�͈͊O�Ɉړ�������ǐՁB
		if (D3DXVec3LengthSq(&PosDiff) > 3.0f)
		{
			//�U�����I����Ă���ړ��J�n�B
			if (!m_animation.IsPlay())
			{
				m_state = EnemyGoblinState::StateFind;
				m_animation.SetAnimationLoopFlag(enAnimAttack, FALSE);
				m_moveSpeed = GOBLINRUNSPEED;
			}

		}
		//�U�����͈ړ����Ȃ��B
		m_move = Vector3Zero;
		break;
	case EnemyGoblinState::StateJump:
		//�W�����v�̃A�j���[�V�������I������痎���ɑJ�ځB
		if (!m_animation.IsPlay())
		{
			m_state = EnemyGoblinState::StateFall;
		}
		break;
	case EnemyGoblinState::StateFall:
		//�������ɒn�ʂɒ��n�B
		if (m_characterController.IsOnGround() == TRUE)
		{
			//���n�ɑJ�ځB
			m_state = EnemyGoblinState::StateLanding;
			//���n�����B
		}
		else
		{
			//�������B
			m_state = EnemyGoblinState::StateFall;
		}
		break;
	case EnemyGoblinState::StateLanding:
		if (m_characterController.IsOnGround() == TRUE)
		{
			//���n�̃A�j���[�V�������I�������ҋ@���v���C���[��ǐՒ��ɂ���B
			if (!m_animation.IsPlay()) {
				m_state = EnemyGoblinState::StateSearch;
			}
		}
		else
		{
			m_state = EnemyGoblinState::StateFall;
		}
		break;
	case EnemyGoblinState::StateDamage:
		//�_���[�W���󂯂���v���C���[������Ԃɂ���B
		if (!m_animation.IsPlay())
		{
			m_state = EnemyGoblinState::StateFind;
		}
		break;
	case EnemyGoblinState::StateDead:
		m_moveSpeed = 0.0f;
		if (!m_animation.IsPlay()) {
			//���S�Ɏ��񂾂�v���C���[�Ɍo���l��n���B
			m_unitytyan->AddPlayerEXP(m_dropEXP);
			//�G�l�~�[�}�l�[�W���[�Ɏ��񂾂��Ƃ�`����t���O��TRUE�ɂ���B
			m_isDead = TRUE;
			//�L�����N�^�[�R���g���[���������B
			m_characterController.RemoveRigidBoby();
		}
		break;
	}

	//�G�l�~�[�̏�Ԃ����čĐ�����A�j���[�V������ݒ�B
	if (m_state == EnemyGoblinState::StateSearch)
	{
		//�~�܂��Ă�����ҋ@�œ����Ă�����������[�V������ݒ�B
		if (m_moveSpeed > GOBLINWAITSPEED)
		{
			//������ݒ�B
			//�������[�V�����B
			m_currentAnimSetNo = enAnimWalk;
		}
		else
		{
			//�ҋ@��ݒ�B
			//�ҋ@���[�V�����B
			m_currentAnimSetNo = enAnimWait;
		}
	}
	//�v���C���[�𔭌��B
	else if (m_state == EnemyGoblinState::StateFind)
	{
		//���胂�[�V�����B
		m_currentAnimSetNo = enAnimRun;
	}
	//�U����ݒ�B
	else if (m_state == EnemyGoblinState::StateAttack)
	{
		//�U�����[�V�����B
		m_currentAnimSetNo = enAnimAttack;
	}
	//�_���[�W��Ԃ�ݒ�B
	else if (m_state == EnemyGoblinState::StateDamage)
	{
		//�_���[�W���[�V�����B
		m_currentAnimSetNo = enAnimDamage;
	}
	//����Ԃ�ݒ�B
	else if (m_state == EnemyGoblinState::StateDead)
	{
		//�����[�V�����B
		m_currentAnimSetNo = enAnimDead;
	}
	//������ԁB
	else if (m_state == EnemyGoblinState::StateFall)
	{
		//�������[�V�����B
		m_currentAnimSetNo = enAnimFall;
	}
	//�W�����v��ԁB
	else if (m_state == EnemyGoblinState::StateJump)
	{
		//�W�����v�A�j���[�V�����B
		m_currentAnimSetNo = enAnimJump;
	}
	else if (m_state == EnemyGoblinState::StateLanding)
	{
		m_currentAnimSetNo = enAnimLanding;
	}

	//�L�����N�^���������x��ݒ�B
	m_characterController.SetMoveSpeed(m_move);
	//�P�t���[���̌o�ߎ��Ԃ̎擾�B
	m_frameDeltaTime = static_cast<GameScene*>(g_pScenes)->GetFrameDeltaTime();
	//�L�����N�^�R���g���[���[�����s�B
	m_characterController.Execute(GetLocalFrameDeltaTime());
	//�L�����N�^�[�R���g���[���Ōv�Z�����ʒu���G�l�~�[�̈ʒu�ɔ��f�B
	m_position = m_characterController.GetPosition();
	m_position.y += 0.7f;

	//�v�Z��������]�̔��f�B
	m_currentAngleY = m_turn.Update(m_isTurn, m_targetAngleY);

	m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);

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
	//����ł����牽�����Ȃ��B
	if (m_state == EnemyGoblinState::StateDamage || m_state == EnemyGoblinState::StateDead)
	{
		return;
	}
	RigidBody* rb = m_characterController.GetRigidBody();
	//�ǂ����ɔ������Ă��铖���蔻���T���Ă���B
	const DamageCollisionWorld::Collision* dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
		DamageCollisionWorld::enDamageToEnemy,
		rb->GetBody()
	);

	if (dmgColli != NULL)
	{
		//�_���[�W���󂯂��B
		m_hp -= dmgColli->damage;
		if (m_hp <= 0.0f) {
			//���S
			m_hp = 0;
			m_state = EnemyGoblinState::StateDead;
		}
		else {
			m_state = EnemyGoblinState::StateDamage;
		}
	}
}