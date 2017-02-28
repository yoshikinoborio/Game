#pragma once
#include "SkinModel.h"
#include <string.h>
#include "RigidBody.h"
#include "MeshCollider.h"
#include "Light.h"

//�}�b�v�`�b�v�̔z�u���B
struct MapLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
	D3DXVECTOR3 scale;			//�X�P�[���B
};

class MapChip
{
public:
	MapChip();
	~MapChip();
	//�������B
	void Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//�X�V�B
	void Update();
	//�`��
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
private:
	SkinModel m_skinModel;			//�X�L�����f���B
	Animation m_animation;			//�A�j���[�V�����B
	SkinModelData* m_skinModelData;	//�X�L�����f���f�[�^�B
	SkinModelDataResources	m_skinModelDataResources;
	MeshCollider	m_meshCollider;	//���b�V���R���C�_�[�B
	RigidBody		m_rigidBody;	//���́B
	Light			m_light;

	D3DXVECTOR3		m_position;		//���W�B
	D3DXVECTOR3     m_scale;		//�X�P�[���B
	D3DXQUATERNION	m_rotation;		//��]�B
	bool			m_drawFlag;

};