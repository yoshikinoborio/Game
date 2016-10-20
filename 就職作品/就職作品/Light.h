#pragma once

const int LIGHT_NUM = 4;	//���C�g�̐�

//���C�g�̃N���X
class Light
{

public:
	Light();
	~Light();

	//���C�g���������B
	void Initialize();

	//���C�g�̍X�V
	void Update();

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
	/*!
	*@brief	���s�����̕�����ݒ�B
	*@param[in]	lightNo		���C�g�̔ԍ�
	*@param[in]	dir			�����B
	*/
	void SetDiffuseLightDirection(int lightNo, const D3DXVECTOR4& dir)
	{
		m_diffuseLightDirection[lightNo] = dir;
	}
	/*!
	*@brief	���s�����̐F��ݒ�B
	*@param[in]	lightNo		���C�g�̔ԍ��B
	*@param[in]	color		���s�����̐F�B
	*/
	void SetDiffuseLightColor(int lightNo, const D3DXVECTOR4& color)
	{
		m_diffuseLightColor[lightNo] = color;
	}
	/*!
	* @brief	������ݒ�B
	*/
	void SetAmbientLight(const D3DXVECTOR4& ambient)
	{
		m_ambientLight = ambient;
	}
	//�����擾
	D3DXVECTOR4 GetAmbientLight()
	{
		return m_ambientLight;
	}
	//���C�g�̐��擾
	int GetLight_Num()
	{
		return LIGHT_NUM;
	}
private:
	D3DXVECTOR4 			m_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
	D3DXVECTOR4				m_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
	D3DXVECTOR4				m_ambientLight;						//����
};