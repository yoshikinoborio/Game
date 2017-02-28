#include "stdafx.h"
#include "EnemySkeleton.h"
#include "SceneManager.h"

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
	m_mostNearCourceIndex = 0;
	m_isDead = FALSE;
	m_unitytyan = g_pScenes->GetUnityChan();
}

EnemySkeleton::~EnemySkeleton()
{
	delete m_skinModelData;
}

void EnemySkeleton::Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale)
{
	//�I���W�i���̃��f������R�s�[(�N���[��)���쐬�B
	m_skinModelData = static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load(modelPath, &m_animation);
	//m_skinModelDataResources.Load(modelPath, &m_animation);
	//�N���[�����g���ď������B
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

	m_light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_skinModel.SetLight(&m_light);
	m_skinModel.SetHasNormalMap(FALSE);

	//�����t�H�O�̃t���O��ݒ�B
	m_skinModel.SetFogDistFlag(TRUE);
	//�����t�H�O�̃p�����[�^�[��ݒ�B
	m_skinModel.SetFogDistParam(150.0f, 300.0f);
	//�����t�H�O�̃t���O��ݒ�
	m_skinModel.SetFogHeightFlag(FALSE);

	//�A�j���[�V�����̐ݒ�B
	m_animation.SetAnimationLoopFlag(enAnimAttack, FALSE);
	m_animation.SetAnimationLoopFlag(enAnimDamage, FALSE);
	m_animation.SetAnimationLoopFlag(enAnimDead, FALSE);

	//Unity�ŏo�͂����������ɐݒ�B
	m_position = pos;
	m_initPos = m_position;
	this->m_rotation = rotation;
	m_scale = scale;

	//���G������J�n�B
	m_state = SkeletonStateSearch;

	//�X�P���g���̔��a�ƍ����B
	m_height = 1.0f;
	m_radius = 0.6f;
	
	float Min;
	Min = 99999;	//�ԕ�
	//�R�[�X��`�̔z��̐����v�Z�B
	m_courceArray = sizeof(EnemyCource) / sizeof(EnemyCource[0]);
	for (int i = 0; i < m_courceArray; i++) {
		D3DXVECTOR3 dist;
		dist = m_position - EnemyCource[i];
		float len = D3DXVec3Length(&dist);
		if (len < Min)
		{
			//��ԋ߂��R�[�X��`���m��
			m_mostNearCourceIndex = i;
			Min = len;//��ԒZ������
		}
	}

	m_hp = 10;

	m_dropEXP = 100;

	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//�d�͋��߁B

}

void EnemySkeleton::Update()
{
	if (m_isDead != TRUE)
	{
		m_animation.Update(GetLocalFrameDeltaTime());

		m_move = m_characterController.GetMoveSpeed();

		m_unityPos = m_unitytyan->GetUnityChanPos();

		m_isTurn = FALSE;

		m_posDifference = m_unityPos - m_position;

		//��������Ɏg���ϐ��B
		D3DXVECTOR3 PosDiff = m_posDifference;

		// �X�P���g���̃��[���h�s����擾�B
		D3DXMATRIX& SkePos = m_skinModel.GetWorldMatrix();

		Damage();

		switch (m_state)
		{
			//���G���B
		case SkeletonStateSearch:
			//�n�ʂɒ����Ă��鎞�B
			if (m_characterController.IsOnGround() == TRUE)
			{

				//�G�̎���p������Ď���p���Ƀv���C���[�����邩�𒲂ׂ�B
				//�����̌����x�N�g���B
				D3DXVECTOR3 Dir = m_move;
				//�v���C���[�ւ̌����x�N�g���B
				D3DXVECTOR3 PlayerDir = PosDiff;
				//��̃x�N�g���𐳋K���B
				D3DXVec3Normalize(&Dir,&Dir);
				D3DXVec3Normalize(&PlayerDir, &PlayerDir);

				//���K��������̃x�N�g���̓��ς��v�Z�B
				float dot = D3DXVec3Dot(&Dir, &PlayerDir);
				//���ς̒l�̋t�]�����烉�W�A�������߂�B
				float rad = acos(dot);
				//���W�A������p�x�ɕϊ������ۂ̊p�x�������߂�B
				float selfangle D3DXToDegree(rad);
				//�����̎���p�ɂ��邩������500�ȉ��̎��B
				if (selfangle < 50.0f&&D3DXVec3LengthSq(&PosDiff) < 500.0f)
				{
					//�����B
					m_state = SkeletonStateFind;
					break;
				}

				////���j�e�B����񂪋߂��ɗ������̏����B
				//if (D3DXVec3LengthSq(&PosDiff) < 500.0f)
				//{
				//	//�����B
				//	m_state = SkeletonStateFind;
				//	break;
				//}
				//�߂��ɂ��Ȃ����͍��G���B
				SearchMove();
			}
			break;
			//�����B
		case SkeletonStateFind:
			m_moveSpeed = SKELETONRUNSPEED;
			FindMove();
			//���G�͈͓��Ƀ��j�e�B�����𔭌��B
			//�������ɋ߂��ɍs���ƍU������B
			if (D3DXVec3LengthSq(&PosDiff) < 10.0f)
			{
				m_state = SkeletonStateAttack;
			}
			if (D3DXVec3LengthSq(&PosDiff) > 250.0f)
			{
				m_state = SkeletonStateSearch;
				m_moveSpeed = SKELETONWAITTIME;
			}
			break;
		case SkeletonStateAttack:
			m_animation.SetAnimationLoopFlag(enAnimAttack, TRUE);
			m_atrTime += DeltaTime;
			//�U�����ɓ����蔻��𐶐��B
			//�X�P���g���̑O�����ɓ����蔻��𔭐�������B
			if (m_atrTime >= 1.2f)
			{
				g_damageCollisionWorld->Add(2.0f, D3DXVECTOR3(SkePos.m[3][0], SkePos.m[3][1], SkePos.m[3][2]), 0.03f, 10, g_damageCollisionWorld->enDamageToPlayer, 0);
				m_atrTime = 0.0f;
			}
			//�U�����Ƀ��j�e�B����񂪍U���\�͈͊O�Ɉړ�������ǐՁB
			if (D3DXVec3LengthSq(&PosDiff) > 10.0f)
			{
				//�U�����I����Ă���ړ��J�n�B
				if (!m_animation.IsPlay())
				{
					m_state = SkeletonStateFind;
					m_animation.SetAnimationLoopFlag(enAnimAttack, FALSE);
				}
			}

			//�U�����͈ړ����Ȃ��B
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

		//�L�����N�^���������x��ݒ�B
		m_characterController.SetMoveSpeed(m_move);
		//�L�����N�^�R���g���[���[�����s�B
		m_characterController.Execute(GetLocalFrameDeltaTime());
		//�L�����N�^�[�R���g���[���Ōv�Z�����ʒu���G�l�~�[�̈ʒu�ɔ��f�B
		m_position = m_characterController.GetPosition();
		//�������������Ə�������玲����肻�̎�����]���Ƃ��ăN�H�[�^�j�I������]�B
		D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_targetAngleY);

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


void EnemySkeleton::FindMove()
{
	m_isTurn = TRUE;

	m_posDifference.y = 0.0f;

	//�v���C���[���ړ�������ǂ݌}�����鏈���B
	m_SkeDir = m_posDifference;

	//�v���C���[�ƓG�̑��Α��x�����߂�B
	D3DXVECTOR3 Vr = m_unitytyan->GetUniDir() - m_SkeDir;
	//�v���C���[�ƓG�̑��΋��������߂�B
	D3DXVECTOR3 Sr = m_unitytyan->GetUnityChanPos() - m_position;
	//�ڋߎ��Ԃ����߂�B
	D3DXVECTOR3 Tc;
	Tc.x = abs(Sr.x) / abs(Vr.x);
	Tc.y = abs(Sr.y) / abs(Vr.y);
	Tc.z = abs(Sr.z) / abs(Vr.z);

	//�}���|�C���g�B
	D3DXVECTOR3 GeigekiPos;
	GeigekiPos.x = m_unitytyan->GetUnityChanPos().x + m_unitytyan->GetUniDir().x * Tc.x;
	GeigekiPos.y = m_unitytyan->GetUnityChanPos().y +m_unitytyan->GetUniDir().y * Tc.y;
	GeigekiPos.y = 0.0f;
	GeigekiPos.z = m_unitytyan->GetUnityChanPos().z + m_unitytyan->GetUniDir().z * Tc.z;

	D3DXVECTOR3 Dir;
	//���ړ��ʁ�||�}���|�C���g�|�G���W||�~�ړ��ʁB
	Dir = GeigekiPos - m_position;
	D3DXVec3Normalize(&Dir, &Dir);

	//�L�����������Ă�������𐳋K���B
	D3DXVec3Normalize(&m_posDifference, &m_posDifference);
	
	//�G�����j�e�B�����̌����ɐi�܂���B
	//m_movesSpeed�Ɋ|����l��Dir�ɂ���Ɛ�ǂ݌^�ɂȂ�B
	m_move.x= m_moveSpeed*m_posDifference.x;
	m_move.z = m_moveSpeed*m_posDifference.z;

	//��]�B
	m_targetAngleY = Turn(m_posDifference);
}

void EnemySkeleton::SearchMove()
{
	m_state = SkeletonStateSearch;
	m_moveSpeed = SKELETONRUNSPEED;
	//�R�[�X��`�ɏ]�����ړ��̏����B
	{
		//�R�[�X��`�Ɍ������x�N�g�������߂�
		D3DXVECTOR3 toCource = EnemyCource[m_mostNearCourceIndex] - m_position;
		//�R�[�X��`�̃x�N�g���̒����𒲂ׂ�B
		float len = D3DXVec3Length(&toCource);
		//���ׂ��R�[�X��`�̃x�N�g���̒�����10.0f�ȉ��Ȃ玟�̃R�[�X��`�ɐi�ށB
		if (len < 10.0f)
		{
			//�R�[�X��`�̔z��̃C���f�b�N�X��i�߂�B
			m_mostNearCourceIndex++;
			//�Ō�̃R�[�X��`�܂ŗ������ԍŏ��̃R�[�X��`�ɖ߂�B
			if (m_mostNearCourceIndex > m_courceArray)
			{
				m_mostNearCourceIndex = 0;
			}
		}
		//�R�[�X��`�Ɍ������x�N�g���̐��K���B
		D3DXVec3Normalize(&toCource, &toCource);

		m_move.x = m_moveSpeed*toCource.x;
		m_move.z = m_moveSpeed*toCource.z;
		//��]�B
		m_targetAngleY = Turn(toCource);
	}

}

void EnemySkeleton::Damage()
{
	//����ł����牽�����Ȃ��B
	if (m_state == SkeletonStateDamage || m_state == SkeletonStateDead)
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
			m_state = SkeletonStateDead;
		}
		else {
			m_state = SkeletonStateDamage;
		}
	}
}

float EnemySkeleton::Turn(D3DXVECTOR3 dir)
{
	//��]�̏����B
	if (D3DXVec3Length(&dir) > 0.0f)
	{
		D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//��]�ʂ̌v�Z�B
		m_targetAngleY = acos(D3DXVec3Dot(&forward, &dir));
		D3DXVECTOR3 axis;
		//�x�N�g���ƃx�N�g���̊O�ς������+,-�ǂ���ɉ񂷂������߂�B
		D3DXVec3Cross(&axis, &forward, &dir);
		D3DXVec3Normalize(&axis, &axis);
		//�����̎���+�ɂ���B
		if (axis.y < 0.0f)
		{
			m_targetAngleY *= -1.0f;
		}
	}

	return m_targetAngleY;
}