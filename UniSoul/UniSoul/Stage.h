#pragma once
#include "AnimationModel3D.h"

//�X�e�[�W�N���X
class Stage :public AnimationModel3D
{
public:
	//�f�X�g���N�^
	Stage();
	//�R���X�g���N�^
	~Stage();
	//������
	void Initialize();
	//�X�V
	void Update()override;
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
	D3DXVECTOR3		m_position;			//���W�B
	D3DXVECTOR3     m_scale;			//�X�P�[���B
	D3DXQUATERNION  m_rotation;			//��]�s��B
};