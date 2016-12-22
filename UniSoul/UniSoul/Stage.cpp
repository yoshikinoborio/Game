#include "stdafx.h"
#include "Game.h"
#include "Stage.h"

Stage::Stage()
{
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

Stage::~Stage()
{
	Release();
}

//�������B
void Stage::Initialize()
{
	m_skinModelData.LoadModelData("image\\Ground.X", &m_animation);
	m_skinModel.Initialize(&m_skinModelData);

	//���C�g�̐ݒ�B
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_skinModel.SetLight(&m_light);
	m_skinModel.SetHasNormalMap(FALSE);

	//�e�`�悷��t���O���Z�b�g
	m_skinModel.SetShadowReceiverFlag(TRUE);
	m_skinModel.Update(m_position, m_rotation, m_scale);
	//��������Փ˔��藍�݂̏������B
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����B
	D3DXMATRIX* rootBoneMatrix = m_skinModelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_skinModel, rootBoneMatrix);
	//�����č��̂��쐬����B
	//�܂��͍��̂��쐬���邽�߂̏���ݒ�B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;	//���̂̃R���W������ݒ肷��B
	rbInfo.mass = 0.0f;					//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	//���̂��쐬�B
	m_rigidBody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	game->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);
	
}

//�X�V�B
void Stage::Update()
{
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

// �`��B
void Stage::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver){

	m_skinModel.Draw(&viewMatrix, &projMatrix,isShadowReceiver);
}

//�J���B
void Stage::Release()
{
	m_skinModelData.Release();
}