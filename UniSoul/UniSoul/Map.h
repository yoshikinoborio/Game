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

	//�}�b�v�I�u�W�F�N�g�𐶐�����ʒu�ƃt���O�̐ݒ�B
	void SetMapObjectCreate(const D3DXVECTOR3& pos,bool flg)
	{
		m_createPos = pos;
		m_createMapFlag = flg;
	}
private:
	std::vector<MapChip*> m_mapChipList;	//�}�b�v�`�b�v�̃��X�g�B
	bool				  m_createMapFlag;	//�}�b�v�쐬�t���O�B
	D3DXVECTOR3			  m_createPos;		//�G�𐶐����鎞�Ɏg���ʒu�����i�[�B
};