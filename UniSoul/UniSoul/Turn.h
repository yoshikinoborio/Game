#pragma once

//�L�����N�^�[�̉�]�B
class Turn
{
public:
	//�R���X�g���N�^�B
	Turn();

	//�f�X�g���N�^�B
	~Turn();

	//��]�����̏������B
	void Turn::Initialize();

	//��]�����̍X�V�B
	float Turn::Update(bool isTurn, float currentAngleY);

	//���݂̕����̎擾�B
	const float& GetCurrentAngleY() const
	{
		return m_currentAngleY;

	}

private:
	float	m_currentAngleY;	//���݂̕����B
	float	m_targetAngleY;		//�������������B
	float	m_turnSpeed;		//��]���x�B
	bool	m_isTurn;			//��]�t���O�B
};