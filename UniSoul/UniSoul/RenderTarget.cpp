#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget()
{
	m_depthSurface = NULL;
	m_texture = NULL;
	m_surface = NULL;
	m_texture = NULL;
}

RenderTarget::~RenderTarget()
{
	Release();
}

void RenderTarget::Create(int w,
	int h,
	int mipLevel,
	D3DFORMAT colorFormat,
	D3DFORMAT depthStencilFormat,
	D3DMULTISAMPLE_TYPE multiSampleType,
	int multiSampleQuality)
{
	//�f�v�X�X�e���V���o�b�t�@�̍쐬(�e�N�X�`���ւ̃����_�����O�Ɏg���[�x�o�b�t�@)
	HRESULT hr = g_pd3dDevice->CreateDepthStencilSurface(
		w,													//�[�x�o�b�t�@�ڃT�C�Y
		h,													//�[�x�o�b�t�@�ڃT�C�Y
		static_cast<D3DFORMAT>(depthStencilFormat),			//�[�x�o�b�t�@�̃t�H�[�}�b�g(16bit)
		static_cast<D3DMULTISAMPLE_TYPE>(multiSampleType),	//���x�ȕ�ԕ��@�̎w��
		multiSampleQuality,									//�摜�̕i�����x���̐ݒ�
		TRUE,												//�[�x�o�b�t�@�̐�����@�̎w��
		&m_depthSurface,									//�[�x�o�b�t�@�̊i�[��������|�C���^�̃A�h���X
		NULL												//���NULL���w��
		);
	//�J���[�o�b�t�@(�����_�����O�^�[�Q�b�g�Ƃ��Ďg�p����e�N�X�`��)���쐬�B
	hr = g_pd3dDevice->CreateTexture(
		w,													//�e�N�X�`���̃T�C�Y
		h,													//�e�N�X�`���̃T�C�Y
		mipLevel,											//�e�N�X�`���̃��x��
		D3DUSAGE_RENDERTARGET,								//�����_�����O�^�[�Q�b�g�Ƃ��ė��p���邱�Ƃ̖���
		static_cast<D3DFORMAT>(colorFormat),				//�e�N�X�`���t�H�[�}�b�g
		D3DPOOL_DEFAULT,									//�e�N�X�`���������̊m�ە��@
		&m_texture,											//�e�N�X�`���̊i�[��������|�C���^�̃A�h���X
		NULL												//���NULL���w��
		);
	//�e�N�X�`�����烌���_�����O�^�[�Q�b�g�ɂ���T�[�t�F�X�̃C���^�[�t�F�[�X�̎擾
	m_texture->GetSurfaceLevel(0, &m_surface);

	m_width = w;
	m_height = h;
}

void RenderTarget::Release()
{
	if (m_texture != nullptr) {
		m_texture->Release();
		m_texture = NULL;
	}
	if (m_depthSurface != nullptr) {
		m_depthSurface->Release();
		m_depthSurface = NULL;
	}
	if (m_surface != NULL) {
		m_surface->Release();
		m_surface = NULL;
	}
}