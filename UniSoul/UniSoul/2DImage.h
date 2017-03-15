#pragma once

class C2DImage
{
public:
	//�R���X�g���N�^�B
	C2DImage();

	//�f�X�g���N�^�B
	~C2DImage();

	//�������B
	void Initialize();

	//�`��B
	void Render();

	//�s��쐬�B
	void SetupMatrices();

	//�摜���g�債�Ĉړ�������̂ł͂Ȃ��Ĉړ����Ă���g�傷�鎖�ɂ����
	//�摜�̌��_���X�v���C�g�̒[�ɗ���B
	void SetupSlideMatrices();

	//�X�P�[���̐ݒ�B
	void SetScale(D3DXVECTOR2& scale)
	{
		m_scale = scale;
	}

	//�ʒu�̐ݒ�B
	void SetPosition(D3DXVECTOR2& position)
	{
		m_position = position;
	}

	//�X�v���C�g�����֐�
	HRESULT CreateSprite();	
protected:
	D3DXVECTOR2				m_position;			//�ʒu���
	float					m_angle;			//��]���
	D3DXVECTOR2				m_scale;			//�X�P�[�����
	LPDIRECT3DTEXTURE9		m_pTexture;			//�e�N�X�`��
	D3DCOLOR				m_backColor;		//�w�i�J���[
	LPCTSTR					m_texFileName;		//�e�N�X�`���t�@�C����
	D3DXVECTOR2				m_texCenter;		//�e�N�X�`���̒��_
	RECT					m_rect;				//�`���`
	D3DXMATRIX				m_transformMatrix;	//�ϊ��s��
	LPD3DXSPRITE			m_pSprite;			//�X�v���C�g
};

