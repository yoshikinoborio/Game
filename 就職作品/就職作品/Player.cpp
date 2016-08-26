#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//�R���X�g���N�^�ŏ��������闝�R��
	//Cplayer pl;
	//pl.Initilize()�̎����Y��ŏ���������ĂȂ��ϐ��𖳂�������
	D3DXMatrixIdentity(&m_world);
	D3DXMatrixIdentity(&m_rotation);
	m_position = D3DXVECTOR3(0.0f, 0.8f, 0.0f);
}

Player::~Player()
{
	Release();
}

//������
void Player::Initialize(LPDIRECT3DDEVICE9 pd3dDevice)
{
	m_model3d.Initialize(pd3dDevice,"image\\unitychan.X");
}

//�X�V
void Player::Update()
{
	if (GetAsyncKeyState('W'))
	{
		m_position.z += 0.1f;
	}

	if (GetAsyncKeyState('S'))
	{
		m_position.z -= 0.1f;
	}

	if (GetAsyncKeyState('A'))
	{
		m_position.x -= 0.1f;
	}

	if (GetAsyncKeyState('D'))
	{
		m_position.x += 0.1f;
	}

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&m_world, m_position.x,m_position.y, m_position.z);
}

// �`��B
void Player::Draw(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight){

	m_model3d.Draw(pd3dDevice,
		viewMatrix,
		projMatrix,
		diffuseLightDirection,
		diffuseLightColor,
		ambientLight,
		m_world,
		m_rotation,
		numDiffuseLight
		);

}

//�J���B
void Player::Release()
{
	m_model3d.Release();
}