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
	//���f���̃��[�h�B
	m_skinModelData = static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load(modelPath, &m_animation);
	
	m_skinModel.Initialize(m_skinModelData);

	//���C�g�̐ݒ�B
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

	//�����t�H�O�̃t���O��ݒ�B
	m_skinModel.SetFogDistFlag(TRUE);
	//�����t�H�O�̃p�����[�^�[��ݒ�B
	m_skinModel.SetFogDistParam(150.0f, 300.0f);
	//�����t�H�O�̃t���O��ݒ�
	m_skinModel.SetFogHeightFlag(FALSE);

	//�A�j���[�V�����̐ݒ�B
	m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimAttack, FALSE);


	//Unity�ŏo�͂����������ɐݒ�B
	m_position = pos;
	m_rotation = rotation;
	m_scale = scale;

	//���a�ƍ����B
	m_height = 2.0f;
	m_radius = 1.5f;

	m_hp = 50;
	m_maxhp = m_hp;

	m_state = EnemyState::enStateSearch;

	m_dropEXP =500000;

	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//�d�͋��߁B
	
	//�e��Ԃł̈ړ��X�s�[�h��ݒ�B
	this->SetMoveSpeed(0.0f, 0.02f*60.0f, 0.2f*60.0f);
}

void EnemyBoss::Update()
{
	m_animation.Update(GetLocalFrameDeltaTime());

	m_move = m_characterController.GetMoveSpeed();

	//�v���C���[�Ɍ������x�N�g���̌v�Z�B
	m_posDifference = m_unitytyan->GetUnityChanPos() - m_position;

	m_isTurn = FALSE;

	//�ǂ����ɔ������Ă��铖���蔻���T���Ă��鏈���B
	DamageSearch();

	//�{�X�̃��[���h�s����擾�B
	D3DXMATRIX& BossPos = m_skinModel.GetWorldMatrix();

	//��������Ɏg���ϐ��B
	D3DXVECTOR3 PosDiff = m_posDifference;

	switch (m_state)
	{
	case EnemyState::enStateSearch: {
		float selfangle;
		//�G�̎���p������Ď���p���Ƀv���C���[�����邩�𒲂ׂ�B
		selfangle = m_CreateViewAngle.CreateView(PosDiff, BossPos);
		//�����̎���p�ɂ��邩������500�ȉ��̎��B
		if (selfangle < 50.0f&&D3DXVec3LengthSq(&PosDiff) < 500.0f)
		{
			//�����B
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
		//�L�����������Ă�������𐳋K���B
		D3DXVec3Normalize(&dir, &work);

		//�G���v���C���[�̌����ɐi�܂���B
		m_move = m_moveSpeed * dir;

		//��]�̏����B
		if (D3DXVec3Length(&work) > 0.0f)
		{
			D3DXVECTOR3 forward = Vector3Forward;
			//��]�ʂ̌v�Z�B
			m_targetAngleY = acos(D3DXVec3Dot(&forward, &dir));
			D3DXVECTOR3 axis;
			//�x�N�g���ƃx�N�g���̊O�ς������+,-�ǂ���ɉ񂷂������߂�B
			D3DXVec3Cross(&axis, &forward, &work);
			D3DXVec3Normalize(&axis, &axis);
			
			if (axis.y < 0.0f)
			{
				m_targetAngleY *= -1.0f;
			}
			//�������������Ə�������玲����肻�̎�����]���Ƃ��ăN�H�[�^�j�I������]�B
			D3DXQuaternionRotationAxis(&m_rotation, &axis, m_currentAngleY);
		}
		m_currentAnimSetNo = EnemyAnimation::enAnimRun;;
		//���G�͈͓��Ƀv���C���[�𔭌��B
		//�������ɋ߂��ɍs���ƍU������B
		if (D3DXVec3LengthSq(&PosDiff) < 10.0f)
		{
			m_state = EnemyState::enStateAttack;
		}
	}
		break;
	case EnemyState::enStateAttack: {
		m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimAttack, TRUE);
		m_atrTime += DeltaTime;
		//�U�����ɓ����蔻��𐶐��B
		//�{�X�̑O�����ɓ����蔻��𔭐�������B
		if (m_atrTime >= 0.7f)
		{
			g_damageCollisionWorld->Add(1.0f, D3DXVECTOR3(BossPos.m[3][0], BossPos.m[3][1], BossPos.m[3][2]), 1.7f, 20, g_damageCollisionWorld->enDamageToPlayer, 0);
			m_atrTime = 0.0f;

		}
		//�U�����Ƀv���C���[���U���\�͈͊O�Ɉړ�������ǐՁB
		if (D3DXVec3LengthSq(&PosDiff) > 11.0f)
		{
			//�U�����I����Ă���ړ��J�n�B
			if (!m_animation.IsPlay())
			{
				m_state = EnemyState::enStateFind;
				m_animation.SetAnimationLoopFlag((int)EnemyAnimation::enAnimAttack, FALSE);
				m_moveSpeed = m_runSpeed;
			}

		}
		m_currentAnimSetNo = EnemyAnimation::enAnimAttack;
		//�U�����͈ړ����Ȃ��B
		m_move = Vector3Zero;
	}
		break;
		//�_���[�W���󂯂Ă���B
	case EnemyState::enStateDamage: {
		DamageProcess();
	}
		break;
		//���񂾏�ԁB
	case EnemyState::enStateDead: {
		m_moveSpeed = 0.0f;
		//���S�Ɏ��񂾂�v���C���[�Ɍo���l��n���B
		m_unitytyan->AddPlayerEXP(m_dropEXP);
		//�G�l�~�[�}�l�[�W���[�Ɏ��񂾂��Ƃ�`����t���O��TRUE�ɂ���B
		m_isDead = TRUE;
		//�L�����N�^�[�R���g���[���[�̉���B
		m_characterController.RemoveRigidBoby();
	}
		break;
	}	

	//�L�����N�^���������x��ݒ�B
	m_characterController.SetMoveSpeed(m_move);
	//�L�����N�^�R���g���[���[�����s�B
	m_characterController.Execute(GetLocalFrameDeltaTime());
	//�L�����N�^�[�R���g���[���Ōv�Z�����ʒu���G�l�~�[�̈ʒu�ɔ��f�B
	m_position = m_characterController.GetPosition();

	//�v�Z��������]�̔��f�B
	m_currentAngleY = m_turn.Update(m_isTurn, m_targetAngleY);

	m_animation.PlayAnimation((int)m_currentAnimSetNo, 0.1f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void EnemyBoss::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowCaster)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowCaster);

	//�P�t���[���̌o�ߎ��Ԃ̎擾�B
	m_frameDeltaTime = static_cast<GameScene*>(g_pScenes)->GetFrameDeltaTime();
}

void EnemyBoss::DamageSearch()
{
	RigidBody* rb = m_characterController.GetRigidBody();
	//�ǂ����ɔ������Ă��铖���蔻���T���Ă���B
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
		//�_���[�W���󂯂đ̗͂����炵������0�ɂȂ�Ȃ���Α̗͂������B
		if (m_hp > 0.0f)
		{
			//�_���[�W���󂯂��B
			m_hp -= dmgColli->damage;
		}
		
		if (m_hp <= 0.0f) {
			//���S
			m_hp = 0;
			m_state = EnemyState::enStateDead;
		}
		else {
			m_state = EnemyState::enStateFind;
		}
	}

	
}
