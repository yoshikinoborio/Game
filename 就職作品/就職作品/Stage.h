#pragma once
#include "Model3D.h"

//�X�e�[�W�N���X
class Stage
{
public:
	//�f�X�g���N�^
	Stage();
	//�R���X�g���N�^
	~Stage();
	//������
	void Initialize(LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V
	void Update();
	//�`��
	void Draw(LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight);
	//���
	void Release();
private:
	Model3D					m_model3d;			//3D�֌W��\������Model3D�̃C���X�^���X��ێ�
	D3DXVECTOR3				m_position;			//���W
	D3DXMATRIX				m_world;			//���[���h�s��
	D3DXMATRIX				m_rotation;			//��]�s��
};