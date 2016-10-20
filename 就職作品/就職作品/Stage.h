#pragma once
#include "NonAnimationModel3D.h"

//�X�e�[�W�N���X
class Stage : NonAnimationModel3D
{
public:
	//�f�X�g���N�^
	Stage();
	//�R���X�g���N�^
	~Stage();
	//������
	void Initialize()override;
	//�X�V
	void Update()override;
	//�`��
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight);
	//���
	void Release();
private:
	D3DXVECTOR3		m_position;			//���W�B
	D3DXMATRIX		m_world;			//���[���h�s��B
	D3DXMATRIX		m_rotation;				//��]�s��B
};