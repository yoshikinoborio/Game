#pragma once
#include <vector>
//���X�|�[���N���X�B
class Respawn
{
public:
	//�R���X�g���N�^�B
	Respawn();

	//�f�X�g���N�^�B
	~Respawn();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();
private:
	std::vector<btGhostObject*>		m_ghostObjectList;	//�S�[�X�g�B���̂̕ς��ɂȂ���́B
};

