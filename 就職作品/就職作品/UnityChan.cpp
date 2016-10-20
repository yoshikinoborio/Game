#include "stdafx.h"
#include "Game.h"
#include "UnityChan.h"

UnityChan::UnityChan()
{
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//D3DXQUATERNION�̈����͉�]��(0.0f�`1.0f��Max);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_animationcount = 0;
}

UnityChan::~UnityChan()
{
	Release();
}

void UnityChan::Initialize()
{
	m_skinModelData.LoadModelData("image\\Unitytyan.X", &m_animation);
	m_skinModel.Initialize(&m_skinModelData);

	m_animation.SetAnimationEndtime(AnimationRun, 0.8f);
	m_animation.SetAnimationEndtime(AnimationJump, 1.6f);
	m_currentAnimSetNo = AnimationInvalid;

	//�J�����̃C���X�^���X�̎擾�B
	m_camera = game->GetCamera();
}
void UnityChan::Update()
{
	m_animation.Update(1.0f / 60.0f);

	//�p�b�h�ɂ��J�����̉��Ɉړ����鏈���B
	PadMove();

	m_currentAnimSetNo = AnimationStand;

	//�p�b�h�̃X�^�[�g�{�^���ŃQ�[���I���B
	if (g_pad.IsPress(enButtonStart))
	{
		PostQuitMessage(0);
	}
	if (g_pad.IsPress(enButtonA))
	{
		m_currentAnimSetNo = AnimationStand;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_position.x += 1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_position.x -= 1.0f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		m_position.z += 1.0f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_position.z -= 1.0f;
	}
	m_animation.PlayAnimation(m_currentAnimSetNo, 1.0f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void UnityChan::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
}

void UnityChan::Release()
{
	m_skinModelData.Release();
}

void UnityChan::PadMove()
{
	//�J�����̕����Ƀv���C���[��i�߂鏈��
	//���X�e�B�b�N����̃J�����s��ɂ�������͂�ێ�
	D3DXVECTOR3 moveDirCameraLocal;
	moveDirCameraLocal.y = 0.0f;
	moveDirCameraLocal.x = g_pad.GetLStickXF();
	moveDirCameraLocal.z = g_pad.GetLStickYF();
	D3DXMATRIX& ViewInv = m_camera->GetViewMatrixInv();//�J�����̋t�s����擾
	//�J������Ԃ��猩���������̃x�N�g�����擾
	D3DXVECTOR3 cameraZ;
	cameraZ.x = ViewInv.m[2][0];
	cameraZ.y = 0.0f;		//Y������Ȃ�
	cameraZ.z = ViewInv.m[2][2];
	D3DXVec3Normalize(&cameraZ, &cameraZ);	//Y����ł������Ă���̂Ő��K������
	//�J�������猩���������̃x�N�g�����擾
	D3DXVECTOR3 cameraX;
	cameraX.x = ViewInv.m[0][0];
	cameraX.y = 0.0f;		//Y���͂���Ȃ�
	cameraX.z = ViewInv.m[0][2];
	D3DXVec3Normalize(&cameraX, &cameraX);	//Y����ł������Ă���̂Ő��K������

	D3DXVECTOR3 moveDir;
	moveDir.x = cameraX.x * moveDirCameraLocal.x + cameraZ.x * moveDirCameraLocal.z;
	moveDir.y = 0.0f;	//Y���͂���Ȃ�
	moveDir.z = cameraX.z * moveDirCameraLocal.x + cameraZ.z * moveDirCameraLocal.z;

	m_position += moveDir;
}