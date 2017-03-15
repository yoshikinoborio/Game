#pragma once
#include "MapChip.h"

class Map
{
public:
	//�R���X�g���N�^�B
	Map();

	//�f�X�g���N�^�B
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
	std::vector<MapChip*> m_mapChipList;	//�}�b�v�`�b�v�̃��X�g�B
};