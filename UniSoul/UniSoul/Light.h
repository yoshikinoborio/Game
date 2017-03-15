#pragma once

namespace {
	const int LIGHT_NUM = 4;	//���C�g�̐�
}

//���C�g�̃N���X
class Light
{

public:
	//�R���X�g���N�^�B
	Light();

	//�f�X�g���N�^�B
	~Light();

	//���C�g���������B
	void Initialize();

	//���C�g�̕����擾
	D3DXVECTOR4* GetDiffuseLightDirection()
	{
		return m_diffuseLightDirection;
	}

	//���C�g�̐F�擾
	D3DXVECTOR4* GetDiffuseLightColor()
	{
		return m_diffuseLightColor;
	}

	//���s�����̕�����ݒ�B
	//���C�g�̔ԍ�
	//�����B
	void SetDiffuseLightDirection(const int& lightNo, const D3DXVECTOR4& dir)
	{
		m_diffuseLightDirection[lightNo] = dir;
	}

	//���s�����̐F��ݒ�B
	//���C�g�̔ԍ��B
	//���s�����̐F�B
	void SetDiffuseLightColor(const int& lightNo, const D3DXVECTOR4& color)
	{
		m_diffuseLightColor[lightNo] = color;
	}

	//������ݒ�B
	void SetAmbientLight(const D3DXVECTOR4& ambient)
	{
		m_ambientLight = ambient;
	}

	//�����擾
	const D3DXVECTOR4& GetAmbientLight() const
	{
		return m_ambientLight;
	}

	//���C�g�̐��擾
	const int& GetLight_Num() const
	{
		return LIGHT_NUM;
	}
private:
	D3DXVECTOR4 			m_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
	D3DXVECTOR4				m_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
	D3DXVECTOR4				m_ambientLight;						//����
};