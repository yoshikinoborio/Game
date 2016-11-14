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
	m_state = SkeletonStateSearch;
	m_height = 0.0f;
	m_radius = 0.0f;
	m_unitytyan = game->GetUnityChan();
}

EnemySkeleton::~EnemySkeleton()
{
	Release();
}

void EnemySkeleton::Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale)
{
	//�I���W�i���̃��f������R�s�[(�N���[��)���쐬�B
	m_skinModelData.CloneModelData(g_orginSkinModelData, &m_animation);
	//�N���[�����g���ď������B
	m_skinModel.Initialize(&m_skinModelData);

	m_position = pos;
	m_initPos = m_position;
	this->m_rotation = rotation;
	m_scale = scale;
	m_state = SkeletonStateWait;
	m_radius = 0.5f;
	m_height = 1.0f;

	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//�d�͋��߁B
}

void EnemySkeleton::Update()
{
	m_animation.Update(1.0f / 60.0f);

	m_move = m_characterController.GetMoveSpeed();

	m_unityPos = m_unitytyan->GetUnityChanPos();

	m_isTurn = FALSE;

	m_posDifference = m_unityPos - m_position;
	
	//�n�ʂɒ����Ă��鎞�B
	if (m_characterController.IsOnGround() == TRUE)
	{
		if (m_state == SkeletonStateSearch)
		{
			//���j�e�B����񂪋߂��ɗ������̏����B
			if (D3DXVec3LengthSq(&m_posDifference) < 200.0f)
			{
				m_state = SkeletonStateFind;
				m_moveSpeed = SKELETONRUNSPEED;
			}
			else
			{
				//�߂��ɂ��Ȃ����͍��G���B
				m_state == SkeletonStateSearch;
				m_moveSpeed = SKELETONWALKSPEED;
			}
			10
		}//���G�͈͓��Ƀ��j�e�B�����𔭌��B
		else if (m_state == SkeletonStateFind)
		{
			//�������ɋ߂��ɍs���ƍU������B
			if (D3DXVec3LengthSq(&m_posDifference) < 10.0f)
			{
				m_state = SkeletonStateAttack;
			}
		}
		//��]�ƈړ��̏����B
		SkeletonMove();

	}

	if (m_state==SkeletonStateSearch)
	{
		m_currentAnimSetNo = enAnimWait;
	}
	else if (m_state == SkeletonStateFind)
	{
		m_currentAnimSetNo = enAnimRun;
	}

	//�L�����N�^���������x��ݒ�B
	m_characterController.SetMoveSpeed(m_move);
	//�L�����N�^�R���g���[���[�����s�B
	m_characterController.Execute();
	//�L�����N�^�[�R���g���[���Ōv�Z�����ʒu���G�l�~�[�̈ʒu�ɔ��f�B
	m_position = m_characterController.GetPosition();

	//�������������Ə�������玲����肻�̎�����]���Ƃ��ăN�H�[�^�j�I������]�B
	D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), m_targetAngleY);

	m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void EnemySkeleton::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
}

void EnemySkeleton::Release()
{
	m_skinModelData.Release();
}

void EnemySkeleton::SkeletonMove()
{
	m_isTurn = TRUE;

	m_posDifference.y = 0.0f;

	//�L�����������Ă�������𐳋K���B
	D3DXVec3Normalize(&m_posDifference, &m_posDifference);
	//�G�����j�e�B�����̌����ɐi�܂���B
	m_move = m_moveSpeed*m_posDifference;

	//��]�̏����B
	if (D3DXVec3Length(&m_posDifference) > 0.0f)
	{
		D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//��]�ʂ̌v�Z�B
		m_targetAngleY = acos(D3DXVec3Dot(&forward, &m_posDifference));
		D3DXVECTOR3 axis;
		//�x�N�g���ƃx�N�g���̊O�ς������+,-�ǂ���ɉ񂷂������߂�B
		D3DXVec3Cross(&axis, &forward, &m_posDifference);
		D3DXVec3Normalize(&axis, &axis);
		//�����̎���+�ɂ���B
		if (axis.y < 0.0f)
		{
			m_targetAngleY *= -1.0f;
		}
	}
}