#pragma once
#include "SkinModel.h"
#include <string.h>
#include "RigidBody.h"
#include "MeshCollider.h"
#include "Light.h"
#define MapObjectNum 356

//�}�b�v�`�b�v�̔z�u���B
struct MapLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
	D3DXVECTOR3 scale;			//�X�P�[���B
};

class Map
{
public:
	Map();
	~Map();
	//�������B
	void Initialize();
	//�X�V�B
	void Update();
	//�`��
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
private:
	int tableSize;					//�ʒu���̃e�[�u����
	SkinModel m_skinModel[MapObjectNum];	//�X�L�����f���B
	Animation m_animation;		//�A�j���[�V�����B
	SkinModelData m_skinModelData[MapObjectNum];//�X�L�����f���f�[�^�B
	MeshCollider	m_meshCollider[MapObjectNum];	//���b�V���R���C�_�[�B
	RigidBody		m_rigidBody[MapObjectNum];		//���́B
	Light			m_light;
};