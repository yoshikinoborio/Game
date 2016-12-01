//�e�N�X�`���̓ǂݍ��݁E�摜�\��
#include "stdafx.h"
#include "2DImage.h"

C2DImage::C2DImage()
{
}


C2DImage::~C2DImage()
{
}

void C2DImage::Initialize()
{
	D3DXIMAGE_INFO imgInfo;										//�摜���i�[�p�\����
	D3DXCreateTextureFromFileEx(g_pd3dDevice, this->m_texFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &imgInfo, NULL, &this->m_pTexture);	//�e�N�X�`���Ǎ�
	this->m_texCenter = D3DXVECTOR2((float)imgInfo.Width / 2, (float)imgInfo.Height / 2);	//�e�N�X�`���̒��_�Z�b�g
	RECT rec = { 0, 0, imgInfo.Width, imgInfo.Height };			//�`��̈�
	memcpy(&this->m_rect, &rec, sizeof(RECT));					//�`��̈�Z�b�g
}

void C2DImage::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);		//�X�v���C�g�`��J�n
	pSprite->SetTransform(&this->m_transformMatrix);	//�ϊ��s��Z�b�g
	pSprite->Draw(this->m_pTexture, &this->m_rect, &D3DXVECTOR3(this->m_texCenter.x, this->m_texCenter.y, 0.0f), NULL, this->m_backColor);	//�X�v���C�g�Ƀe�N�X�`���\�t��
	pSprite->End();	//�X�v���C�g�`��I��
}

void C2DImage::SetupMatrices()
{
	D3DXMatrixIdentity(&this->m_transformMatrix);	//���[���h�s�񏉊���
	D3DXMatrixTransformation2D(&this->m_transformMatrix, NULL, 0.0f, &this->m_scale, NULL, D3DXToRadian(this->m_angle), &this->m_position);	//�ϊ��s��쐬
}

void C2DImage::SetupMatrices2()
{
	D3DXMatrixIdentity(&this->m_transformMatrix);	//���[���h�s�񏉊���

	//�摜�̔������炵�Ă���B
	D3DXMatrixTranslation(&this->m_transformMatrix, 65.0f, 0.0f, 0.0f);
	//D3DXMatrixTransformation2D(&this->m_transformMatrix, NULL, 0.0f, &this->m_scale, NULL, D3DXToRadian(this->m_angle), this->m_position);	//�ϊ��s��쐬

	//���炵���l����ϊ��s��̍쐬�B
	{
		D3DXMATRIX scale;
		D3DXMATRIX rotation;
		D3DXMATRIX position;
		D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, 1.0f);
		D3DXMatrixRotationYawPitchRoll(&rotation, 0.0f, 0.0f, m_angle);
		D3DXMatrixTranslation(&position, m_position.x, m_position.y, 0.0f);
		m_transformMatrix = m_transformMatrix*scale*rotation*position;
	}
	//���炵������߂��B
	m_transformMatrix._41 -= 65.0f;
}
