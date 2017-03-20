#include "stdafx.h"
#include "SceneManager.h"
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
	m_cameraFreeFlag = FALSE;
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

	//�v���C���[�̃C���X�^���X�̎擾�B
	m_unitychan = g_pScenes->GetUnityChan();
	
	
	//�����_���王�_�Ɍ������x�N�g���̎Z�o�B
	m_toEyeptVector = m_eyePt - m_lookatPt;

}

//�J�����̍X�V�B
void Camera::Update()
{
	// ��ʂ��~�߂�or�Đ����鏈���B
	GameStop();

	//�p�b�h����擾�����������ɃJ��������]�����鏈���B
	if (m_cameraFreeFlag == FALSE)
	{
		//�p�b�h���g�����J�����̉�]�����B
		PadUseRotation();
		//�J�������v���C���[�ɒǏ]���鏈���B
		TargetPlayer();
	}

//DEBUG���̂ݍs���B
#ifdef _DEBUG
	FreeCameraFlagChanger();
	//�t���[�J�������[�h�ł̏����B
	FreeCameraMode();
#endif // _DEBUG
	
	//�J�����̃r���[�s��ƃp�[�X�y�N�e�B�u�ˉe�s��̍쐬�B
	CameraMatrixUpadate();

	//�J�����t�s��̌v�Z(�J�����̃��[���h�s��̋t�s��)�B
	D3DXMatrixInverse(&m_viewMatrixInv, NULL, &m_viewMatrix);
	
	//�Q�[���̏I���B
	GameEnd();
}

void Camera::PadUseRotation()
{
	//�E�X�e�B�b�N����̓��͂��擾�B
	m_rStick_x = g_pad.GetRStickXF();
	m_rStick_y = g_pad.GetRStickYF();

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
}

void Camera::FreeCameraMode()
{
	if (m_cameraFreeFlag == TRUE) {
		D3DXVECTOR3 moveDirCameraLocal;
		moveDirCameraLocal.y = 0.0f;
		moveDirCameraLocal.x = g_pad.GetLStickXF();
		moveDirCameraLocal.z = g_pad.GetRStickYF();

		D3DXMATRIX& ViewInv = m_viewMatrixInv;//�J�����̋t�s����擾�B
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

		m_moveDir.x += cameraX.x * moveDirCameraLocal.x + cameraZ.x * moveDirCameraLocal.z;
		m_moveDir.y = 0.0f;	//Y���͂���Ȃ��B
		m_moveDir.z += cameraX.z * moveDirCameraLocal.x + cameraZ.z * moveDirCameraLocal.z;

		m_eyePt.x = m_moveDir.x*2.0f;
		m_eyePt.y += g_pad.GetLStickYF() *1.0f;
		m_eyePt.z = m_moveDir.z*2.0f;

		m_lookatPt = m_eyePt;
		m_lookatPt.z += 2.0f;

		if (g_pad.IsTrigger(enButtonA))
		{
			g_enemyManager->SetCreateEnemyFlag(TRUE);
			g_enemyManager->SetCreatePos(m_lookatPt);
		}

		//�t���[�J�����t���O�̑���B
		FreeCameraFlagChanger();
	}
}

void Camera::GameStop()
{
	//�Q�[���ł����g��Ȃ��̂ŃL���X�g�Q�[���V�[���N���X�ɃL���X�g�B
	if (static_cast<GameScene*>(g_pScenes)->GetStopFlag() == FALSE)
	{
		//�Q�[���̒�~�B
		if (g_pad.IsTrigger(enButtonStart))
		{
			static_cast<GameScene*>(g_pScenes)->SetStopFlag(TRUE);
		}
	}
	else
	{
		//�Q�[���̍Đ��B
		if (g_pad.IsTrigger(enButtonStart))
		{
			static_cast<GameScene*>(g_pScenes)->SetStopFlag(FALSE);
		}
	}
}

void Camera::CameraMatrixUpadate()
{
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

void Camera::TargetPlayer()
{
	D3DXVECTOR3 V = m_unitychan->GetUnityChanPos();
	V.y += 2.0f;
	m_lookatPt = V;	//�����_���v���C���[�̏�����ɐݒ�B
	m_eyePt = V + m_toEyeptVector;	//�J�������v���C���[�𒆐S�ɂ��Ĉړ�������B
}

void Camera::GameEnd()
{
	//�p�b�h�̃Z���N�g�{�^���ŃQ�[���I���B
	if (g_pad.IsPress(enButtonSelect))
	{
		PostQuitMessage(0);
	}
}

void Camera::FreeCameraFlagChanger()
{
	if (g_pad.IsTrigger(enButtonUp))
	{
		m_cameraFreeFlag = TRUE;
	}

	if (g_pad.IsTrigger(enButtonDown))
	{
		m_cameraFreeFlag = FALSE;
	}
}