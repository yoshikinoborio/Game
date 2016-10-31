#pragma once
#include "AnimationModel3D.h"

//��N���X
class Sky : AnimationModel3D
{
public:
	Sky();
	~Sky();
	//�������B
	void Initialize()override;
	//�X�V�B
	void Update()override;
	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
		bool isShadowReceiver);
	//����B
	void Release();
private:
	D3DXVECTOR3		m_position;			//���W�B
	D3DXVECTOR3     m_scale;			//�X�P�[���B
	D3DXMATRIX		m_world;			//���[���h�s��B
	D3DXQUATERNION  m_rotation;			//��]�s��B
	bool			m_isShadowReceiver;		//�V���h�E���V�[�o�[�B
};