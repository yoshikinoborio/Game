#pragma once
#include "AnimationModel3D.h"
#include "Light.h"

//��N���X
class Sky : public AnimationModel3D
{
public:
	Sky();
	~Sky();
	//�������B
	void Initialize();
	//�X�V�B
	void Update()override;
	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
private:
	D3DXVECTOR3		m_position;			//���W�B
	D3DXVECTOR3     m_scale;			//�X�P�[���B
	D3DXMATRIX		m_world;			//���[���h�s��B
	D3DXQUATERNION  m_rotation;			//��]�s��B
	bool			m_isShadowReceiver;		//�V���h�E���V�[�o�[�B
	Light			m_light;
};