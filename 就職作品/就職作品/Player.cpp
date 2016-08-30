#include "stdafx.h"
#include "Game.h"
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
	//�J�����̃C���X�^���X�̎擾
	m_camera = game->GetCamera();
}

//�X�V
void Player::Update()
{
	//�J�����̕����Ƀv���C���[��i�߂鏈��
	//���X�e�B�b�N����̃J�����s��ɂ�������͂�ێ�
	D3DXVECTOR3 moveDirCameraLocal;
	moveDirCameraLocal.y = 0.0f;
	moveDirCameraLocal.x = g_pad.GetLStickXF();
	moveDirCameraLocal.z = g_pad.GetLStickYF();
	D3DXMATRIX& ViewInv = m_camera->GetViewMatrixInv();//�J�����̋t�s����擾
	//�J������Ԃ��猩���������̃x�N�g�����擾�B
	D3DXVECTOR3 cameraZ;
	cameraZ.x = ViewInv.m[2][0];
	cameraZ.y = 0.0f;		//Y������Ȃ��B
	cameraZ.z = ViewInv.m[2][2];
	D3DXVec3Normalize(&cameraZ, &cameraZ);	//Y����ł������Ă���̂Ő��K������B
	//�J�������猩���������̃x�N�g�����擾�B
	D3DXVECTOR3 cameraX;
	cameraX.x = ViewInv.m[0][0];
	cameraX.y = 0.0f;		//Y���͂���Ȃ��B
	cameraX.z = ViewInv.m[0][2];
	D3DXVec3Normalize(&cameraX, &cameraX);	//Y����ł������Ă���̂Ő��K������B

	D3DXVECTOR3 moveDir;
	moveDir.x = cameraX.x * moveDirCameraLocal.x + cameraZ.x * moveDirCameraLocal.z;
	moveDir.y = 0.0f;	//Y���͂���Ȃ��B
	moveDir.z = cameraX.z * moveDirCameraLocal.x + cameraZ.z * moveDirCameraLocal.z;

	m_position += moveDir;

	//�Q�[���I��
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&m_world, m_position.x, m_position.y, m_position.z);
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