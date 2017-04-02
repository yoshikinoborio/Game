#pragma once
#include "CharacterController.h"

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
	CharacterController m_characterController;
	D3DXVECTOR3 		m_position;
	D3DXVECTOR3 		m_size;
	D3DXQUATERNION      m_rotation;
	btBoxShape*			m_GhostShape;	//�����蔻�肾��������R���W�����`��B
	btGhostObject*		m_ghostObject;	//�S�[�X�g�B���̂̕ς��ɂȂ���́B
};

