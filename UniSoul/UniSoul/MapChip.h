#pragma once
#include "AnimationModel3D.h"
#include <string.h>

namespace {
	//�}�b�v�`�b�v�̔z�u���B
	struct MapLocInfo {
		const char* modelName;		//���f���B
		D3DXVECTOR3	pos;			//���W�B
		D3DXQUATERNION	rotation;	//��]�B
		D3DXVECTOR3 scale;			//�X�P�[���B
	};
}

class MapChip :public AnimationModel3D
{
public:
	
	//�R���X�g���N�^�B
	MapChip();

	//�f�X�g���N�^�B
	~MapChip();

	//�������B
	void Initialize(const char* modelPath, const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation);

	//�X�V�B
	void Update();

	//�`��
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
};