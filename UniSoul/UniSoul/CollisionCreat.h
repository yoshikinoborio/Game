#pragma once
#include <vector>
#include "RigidBody.h"

//�����Ȃ������蔻����쐬����N���X�B
class CollisionCreat
{
public:
	//�R���X�g���N�^�B
	CollisionCreat();

	//�f�X�g���N�^�B
	~CollisionCreat();

	//�������B
	void Initialize();
private:
	std::vector<btGhostObject*>		m_ghostObjectList;	//�S�[�X�g�B���̂̕ς��ɂȂ���́B
	//std::vector<RigidBody*>			m_rigidBodyList;	//���́B
	//RigidBody						m_rigidBody;	//���́B
};