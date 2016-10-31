#pragma once
#include "SkinModel.h"
#include <string.h>
#define MapObjectNum 7

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
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
		bool isShadowReceiver);
	//���
	void Release();
private:
	int tableSize;					//�ʒu���̃e�[�u����
	SkinModel m_skinModel[MapObjectNum];	//�X�L�����f���B
	Animation m_animation;		//�A�j���[�V�����B
	SkinModelData m_skinModelData[MapObjectNum];//�X�L�����f���f�[�^�B
};

