#pragma once
#include "AnimationModel3D.h"
#include <string.h>
#define MapEnemyNum 2

//�}�b�v�`�b�v�̔z�u���B
struct EnemyLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
	D3DXVECTOR3 scale;			//�X�P�[���B
};
class Enemy : AnimationModel3D
{
public:
	Enemy();
	~Enemy();
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
	SkinModel m_skinModel[MapEnemyNum];	//�X�L�����f���B
	Animation m_animation;		//�A�j���[�V�����B
	SkinModelData m_skinModelData[MapEnemyNum];//�X�L�����f���f�[�^�B
};

