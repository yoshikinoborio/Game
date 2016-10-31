#include "stdafx.h"
#include "Game.h"
#include "UnityChan.h"

UnityChan::UnityChan()
{
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//D3DXQUATERNION�̈����͉�]��(0.0f�`1.0f��Max);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveSpeed = 0.0f;
	m_isTurn = FALSE;
}

UnityChan::~UnityChan()
{
	Release();
}

void UnityChan::Initialize()
{
	//���f���̃��[�h�B
	m_skinModelData.LoadModelData("image\\Unitytyan.X", &m_animation);
	m_skinModel.Initialize(&m_skinModelData);

	//�A�j���[�V�����̏I�����Ԃ̐ݒ�B
	m_animation.SetAnimationEndtime(AnimationRun, 0.84f);
	m_animation.SetAnimationEndtime(AnimationSLID, 1.5f);
	m_animation.SetAnimationEndtime(AnimationBackStep, 1.1f);
	
	//�A�j���[�V�����̃��[�v�ݒ�B
	m_animation.SetAnimationLoopFlag(AnimationSLID,FALSE);
	m_animation.SetAnimationLoopFlag(AnimationBackStep, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationWait_01, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationWait_02, FALSE);

	//�A�j���[�V�����ԍ��̏������B
	m_currentAnimSetNo = AnimationInvalid;
	
	//�Q�[���J�n���͑ҋ@�B
	m_state = StateWait_00;

	//��]�����̃N���X�̏������B
	m_turn.Initialize();

	//�J�����̃C���X�^���X�̎擾�B
	m_camera = game->GetCamera();
}
void UnityChan::Update()
{
	m_animation.Update(1.0f / 60.0f);

	m_isTurn = FALSE;

	//�����Ă���A�~�܂��Ă��鎞�̏����B
	if (m_state == StateRun || m_state == StateWait_00)
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

		//���͂��ꂽ�l����ړ��ʂ����߂Ĉ��l���z�����瑖��ɑJ�ڂ���B
		if (D3DXVec3LengthSq(&m_moveDir) > 0.6f)
		{
			//�����ԁB
			m_state = StateRun;

			//���鎞�̃X�s�[�h�B
			m_moveSpeed = RUNSPEED;

			//�����Ă���r����A�{�^�����������ƃX���C�f�B���O�B
			if (g_pad.IsPress(enButtonA))
			{
				m_state = StateSLID;
			}
		}
		else
		{
			//�������̃X�s�[�h�B
			m_moveSpeed = WALKSPEED;
		}

		//�ҋ@��Ԃ̎��B
		if (m_state == StateWait_00)
		{
			//�ҋ@����A�{�^���������ƃo�b�N�X�e�b�v�B
			if (g_pad.IsPress(enButtonA))
			{
				m_state = StateBackStep;
				
			}
		}
	}
	else if (m_state == StateSLID)
	{
		m_position += m_moveDir*RUNSPEED;
		//�X���C�f�B�����I��������ҋ@�ɑJ�ځB
		if (!m_animation.IsPlay())
		{
			m_state = StateWait_00;
		}
	}
	else if (m_state == StateBackStep)
	{
		//�o�b�N�X�e�b�v���I��������ҋ@�ɑJ�ځB
		if (!m_animation.IsPlay())
		{
			m_state = StateWait_00;
		}
	}

	//�v���C���[�̏�Ԃ����čĐ�����A�j���[�V������ݒ�B
	if (m_state == StateWait_00)
	{
		//�ҋ@(����)��ݒ�B
		m_currentAnimSetNo = AnimationWait_00;
	}
	else if (m_state == StateWait_01)
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
		if (m_moveSpeed == RUNSPEED)
		{
			//�����ݒ�
			m_currentAnimSetNo = AnimationRun;
		}
		else
		{
			//������ݒ�B
			m_currentAnimSetNo = AnimationWalk;
		}

		if (m_state == StateSLID)
		{
			//�X���C�f�B���O��ݒ�B
			m_currentAnimSetNo = AnimationSLID;
		}
	}

	//�p�b�h�̃X�^�[�g�{�^���ŃQ�[���I���B
	if (g_pad.IsPress(enButtonStart))
	{
		PostQuitMessage(0);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_position.x += 1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_position.x -= 1.0f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		m_position.z += 1.0f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_position.z -= 1.0f;
	}

	m_currentAngleY = m_turn.Update(m_isTurn, m_targetAngleY);

	m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void UnityChan::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
}

void UnityChan::Release()
{
	m_skinModelData.Release();
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

	m_position += m_moveDir*m_moveSpeed;
	//�J�����������Ă�������𐳋K���B
	D3DXVec3Normalize(&m_moveDir, &m_moveDir);

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