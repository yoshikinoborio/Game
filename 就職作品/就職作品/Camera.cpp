#include "stdafx.h"
#include "Game.h"
#include "Camera.h"

Camera::Camera()
{
	//������
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

//�J�����̏�����
void Camera::Initialize()
{
	m_near = 0.1f;
	m_far = 1000.0f;
	m_aspect = 1.0f;

	m_eyePt = D3DXVECTOR3(0.0f, 7.0f, -20.0f);
	m_lookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_upVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�v���C���[�̃C���X�^���X�̎擾
	m_player = game->GetPlayer();
	
	//�����_���王�_�Ɍ������x�N�g���̎Z�o
	m_toEyeptVector = m_eyePt - m_lookatPt;

}

//�J�����̍X�V
void Camera::Update()
{
	//�E�X�e�B�b�N����̓��͂��擾
	m_rStick_x = g_pad.GetRStickXF();
	m_rStick_y = g_pad.GetRStickYF();

	//�J�������v���C���[�ɒǏ]���鏈��
	D3DXVECTOR3 V = m_player->GetPlayerPos();
	V.y += 1.0f;
	m_lookatPt = V;	//�����_���v���C���[�̏�����ɐݒ�
	m_eyePt = V + m_toEyeptVector;	//�J�������v���C���[�𒆐S�ɂ��Ĉړ�������

	//�E�X�e�B�b�N���g�����c�̃J�����ړ�
	if (fabsf(m_rStick_y) > 0.0f) {
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &m_upVec, &m_toEyeptVector);//������Ɖ������ɒ��s����x�N�g�������߂�
		D3DXQuaternionRotationAxis(&m_zAxis, &Cross, 0.1f*m_rStick_y);//��ŋ��߂��x�N�g������]���ɂ��ăN�H�[�^�j�I������]
		D3DXMatrixRotationQuaternion(&m_rot, &m_zAxis);//�N�H�[�^�j�I�������]�s����쐬
		D3DXVec3Transform(&m_v4, &m_toEyeptVector, &m_rot);//��]�s����g����m_toEyeptVector����]
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

	//�E�X�e�B�b�N���g�������̃J�����ړ�
	if (fabsf(m_rStick_x) > 0.0f) {
		//Y������̉�]���v�Z
		D3DXQuaternionRotationAxis(&m_yAxis, &m_upVec,0.1f * m_rStick_x);//Y����C�ӂ̉�]���ɂ��ăN�H�[�^�j�I������]
		D3DXMatrixRotationQuaternion(&m_rot, &m_yAxis);//�N�H�[�^�j�I�������]�s����쐬
		D3DXVec3Transform(&m_v4, &m_toEyeptVector, &m_rot);//��]�s����g����m_toEyeptVector����]
		m_toEyeptVector.x = m_v4.x;
		m_toEyeptVector.y = m_v4.y;
		m_toEyeptVector.z = m_v4.z;
	}

	//�J�����t�s��̌v�Z(�J�����̃��[���h�s��̋t�s��)
	D3DXMatrixInverse(&m_viewMatrixInv, NULL, &m_viewMatrix);

	//������W�n�r���[�s����쐬����
	D3DXMatrixLookAtLH(&m_viewMatrix,	//������W�n�r���[�s��@D3DXMATRIX�\���̂ւ̃|�C���^
		&m_eyePt,						//���_���`���� D3DXVECTOR3�\���̂ւ̃|�C���^(���s�ړ��Ŏg����)
		&m_lookatPt,					//�J�����̒����Ώۂ��`���� D3DXVECTOR3�\���̂ւ̃|�C���^
		&m_upVec						//���[���h�̏���A��ʂɂ�(0,1,0)���`���� D3DXVECTOR3�\���̂ւ̃|�C���^
		);

	//����Ɋ�Â��āA������W�n�̃p�[�X�y�N�e�B�u�ˉe�s��(3D���E�ŉ��ߖ@����������s��)���쐬
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix,		//������W�n�̃p�[�X�y�N�e�B�u�ˉe�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�[��Ԃ�
		D3DX_PI / 4,									//y�����̎���p (��p)
		m_aspect,										//�A�X�y�N�g��
		m_near,											//�߂��̃r���[�v���[����z�l(�V�[���̉��s���������ǂ�����ǂ��܂ŕ`�悷�邩�̐ݒ�)
		m_far											//�����̃r���[�v���[����z�l
		);

}