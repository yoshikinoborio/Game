#include "stdafx.h"
#include "Game.h"
#include "Camera.h"

Camera::Camera()
{
	m_eyePt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_lookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_upVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_near = 0.0f;
	m_far = 0.0f;
	m_aspect = 0.0f;
	m_angle = 0.0f;
	m_toEyeptVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rStick_x = 0.0f;
	m_rStick_y = 0.0f;
}

Camera::~Camera()
{

}

//�J�����̏������B
void Camera::Initialize()
{
	m_near = 0.1f;
	m_far = 10000.0f;
	m_aspect = 1920.0f / 1020.0f;

	m_eyePt = D3DXVECTOR3(0.0f, 4.0f, -5.0f);
	m_lookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_upVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���j�e�B�����̃C���X�^���X�̎擾�B
	m_unitychan = game->GetUnityChan();
	
	//�����_���王�_�Ɍ������x�N�g���̎Z�o�B
	m_toEyeptVector = m_eyePt - m_lookatPt;

}

//�J�����̍X�V�B
void Camera::Update()
{
	//�E�X�e�B�b�N����̓��͂��擾�B
	m_rStick_x = g_pad.GetRStickXF();
	m_rStick_y = g_pad.GetRStickYF();

	// ��ʂ��~�߂�or�Đ����鏈���B
	if (game->GetStopFlag() == FALSE)
	{
		if (g_pad.IsTrigger(enButtonStart))
		{
			game->SetStopFlag(TRUE);
		}
	}
	else
	{
		if (g_pad.IsTrigger(enButtonStart))
		{
			game->SetStopFlag(FALSE);
		}
	}

	//�p�b�h�̃X�^�[�g�{�^���ŃQ�[���I���B
	if (g_pad.IsPress(enButtonSelect))
	{
		PostQuitMessage(0);
	}
	
	//�J���������j�e�B�����ɒǏ]���鏈���B
	D3DXVECTOR3 V = m_unitychan->GetUnityChanPos();
	V.y += 2.0f;
	m_lookatPt = V;	//�����_�����j�e�B�����̏�����ɐݒ�B
	m_eyePt = V + m_toEyeptVector;	//�J�������v���C���[�𒆐S�ɂ��Ĉړ�������B

	//�E�X�e�B�b�N���g�����c�̃J�����ړ��B
	if (fabsf(m_rStick_y) > 0.0f) {
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &m_upVec, &m_toEyeptVector);//������Ɖ������ɒ��s����x�N�g�������߂�B
		D3DXQuaternionRotationAxis(&m_zAxis, &Cross, 0.03f*m_rStick_y);//��ŋ��߂��x�N�g������]���ɂ��ăN�H�[�^�j�I������]�B
		D3DXMatrixRotationQuaternion(&m_rot, &m_zAxis);//�N�H�[�^�j�I�������]�s����쐬�B
		D3DXVec3Transform(&m_v4, &m_toEyeptVector, &m_rot);//��]�s����g����m_toEyeptVector����]�B
		D3DXVECTOR3 m_toEyeptVectorOld = m_toEyeptVector;
		m_toEyeptVector.x = m_v4.x;
		m_toEyeptVector.y = m_v4.y;
		m_toEyeptVector.z = m_v4.z;
		D3DXVECTOR3 toPosDir;
		D3DXVec3Normalize(&toPosDir, &m_toEyeptVector);
		if (toPosDir.y < -0.5f) {
			//�J����������������B
			m_toEyeptVector = m_toEyeptVectorOld;
		}
		else if (toPosDir.y > 0.8f) {
			//�J�����������������B
			m_toEyeptVector = m_toEyeptVectorOld;
		}
	}

	//�E�X�e�B�b�N���g�������̃J�����ړ��B
	if (fabsf(m_rStick_x) > 0.0f) {
		//Y������̉�]���v�Z�B
		D3DXQuaternionRotationAxis(&m_yAxis, &m_upVec, 0.03f * m_rStick_x);//Y����C�ӂ̉�]���ɂ��ăN�H�[�^�j�I������]�B
		D3DXMatrixRotationQuaternion(&m_rot, &m_yAxis);//�N�H�[�^�j�I�������]�s����쐬�B
		D3DXVec3Transform(&m_v4, &m_toEyeptVector, &m_rot);//��]�s����g����m_toEyeptVector����]�B
		m_toEyeptVector.x = m_v4.x;
		m_toEyeptVector.y = m_v4.y;
		m_toEyeptVector.z = m_v4.z;
	}

	//�J�����t�s��̌v�Z(�J�����̃��[���h�s��̋t�s��)�B
	D3DXMatrixInverse(&m_viewMatrixInv, NULL, &m_viewMatrix);

	//������W�n�r���[�s����쐬����B
	D3DXMatrixLookAtLH(&m_viewMatrix,	//������W�n�r���[�s��@D3DXMATRIX�\���̂ւ̃|�C���^�B
		&m_eyePt,						//���_���`���� D3DXVECTOR3�\���̂ւ̃|�C���^(���s�ړ��Ŏg����)�B
		&m_lookatPt,					//�J�����̒����Ώۂ��`���� D3DXVECTOR3�\���̂ւ̃|�C���^�B
		&m_upVec						//���[���h�̏���A��ʂɂ�(0,1,0)���`���� D3DXVECTOR3�\���̂ւ̃|�C���^�B
		);

	//����Ɋ�Â��āA������W�n�̃p�[�X�y�N�e�B�u�ˉe�s��(3D���E�ŉ��ߖ@����������s��)���쐬�B
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix,		//������W�n�̃p�[�X�y�N�e�B�u�ˉe�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�[��Ԃ��B
		D3DX_PI / 4,									//y�����̎���p (��p)�B
		m_aspect,										//�A�X�y�N�g��B
		m_near,											//�߂��̃r���[�v���[����z�l(�V�[���̉��s���������ǂ�����ǂ��܂ŕ`�悷�邩�̐ݒ�)�B
		m_far											//�����̃r���[�v���[����z�l�B
		);

}