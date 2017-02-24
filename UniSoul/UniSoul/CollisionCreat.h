#pragma once
#include <vector>
#include "RigidBody.h"

//�R���W�����̔z�u���B
struct CollsionInfo {
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
	D3DXVECTOR3 scale;			//�X�P�[���B
};

//�����Ȃ������蔻����쐬����N���X�B
class CollisionCreat
{
public:
	CollisionCreat();
	~CollisionCreat();
	void Initialize();
private:
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	std::vector<btBoxShape*>	m_cllisionShape;	//�R���W�����`��B
	RigidBody		m_rigidBody;	//���́B
};

