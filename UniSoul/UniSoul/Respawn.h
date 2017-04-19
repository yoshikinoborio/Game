#pragma once
#include <vector>
#include "ParticleEmitter.h"

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

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
private:
	std::vector<btGhostObject*>		m_ghostObjectList;	//�S�[�X�g�I�u�W�F�N�g�B
	CParticleEmitter*				m_pEmitter;
	D3DXVECTOR3						m_postion;
};

