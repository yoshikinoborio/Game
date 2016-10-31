#include "stdafx.h"
#include "Game.h"
#include "ShadowMapCamera.h"

ShadowMapCamera::ShadowMapCamera()
{
	m_shadowmapcameraeyePt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shadowmapcameralookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shadowmapcameraupvec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shadowmapcameranear = 0.0f;
	m_shadowmapcamerafar = 0.0f;
	m_shadowmapcameraaspect = 0.0f;
}

ShadowMapCamera::~ShadowMapCamera()
{

}

//�V���h�E�J�����̏������B
void ShadowMapCamera::Initialize()
{
	m_shadowmapcameranear = 0.1f;
	m_shadowmapcamerafar = 1000.0f;
	m_shadowmapcameraaspect = 1920.0f / 1020.0f;

	m_shadowmapcameraeyePt = D3DXVECTOR3(0.0f, 50.0f, -2.0f);
	m_shadowmapcameralookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shadowmapcameraupvec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//���j�e�B�����̃C���X�^���X�̎擾�B
	//m_unitychan = game->GetUnityChan();

	//�����_���王�_�Ɍ������x�N�g���̎Z�o�B
	//m_toEyeptVector = m_shadowmapcameraeyePt - m_shadowmapcameralookatPt;
}

//�V���h�E�J�����̍X�V�B
void ShadowMapCamera::Update()
{
	//�J���������j�e�B�����ɒǏ]���鏈���B
	//D3DXVECTOR3 V = m_unitychan->GetUnityChanPos();
	//V.y += 1.0f;
	//m_shadowmapcameralookatPt = V;	//�����_�����j�e�B�����̏�����ɐݒ�B
	//m_shadowmapcameraeyePt = V + m_toEyeptVector;	//�J�������v���C���[�𒆐S�ɂ��Ĉړ�������B

	//������W�n�r���[�s����쐬����B
	D3DXMatrixLookAtLH(&m_shadowmapcameraviewMatrix,	
		&m_shadowmapcameraeyePt,						
		&m_shadowmapcameralookatPt,						
		&m_shadowmapcameraupvec							
		);
		
	//����Ɋ�Â��āA������W�n�̃p�[�X�y�N�e�B�u�ˉe�s��(3D���E�ŉ��ߖ@����������s��)���쐬�B
	D3DXMatrixPerspectiveFovLH(&m_shadowmapcameraprojectionMatrix,		//������W�n�̃p�[�X�y�N�e�B�u�ˉe�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�[��Ԃ��B
		D3DX_PI / 2,													//y�����̎���p (��p)�B
		m_shadowmapcameraaspect,										//�A�X�y�N�g��B
		m_shadowmapcameranear,											//�߂��̃r���[�v���[����z�l(�V�[���̉��s���������ǂ�����ǂ��܂ŕ`�悷�邩�̐ݒ�)�B
	    m_shadowmapcamerafar											//�����̃r���[�v���[����z�l�B
		);

}