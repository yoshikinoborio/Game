#include "stdafx.h"
#include "Stage.h"
#include "SceneManager.h"
#include "GameScene.h"

Stage::Stage()
{
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

Stage::~Stage()
{
	delete m_skinModelData;
}

//�������B
void Stage::Initialize()
{
	m_skinModelData = static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load("image\\UniSoulGround.X", &m_animation);

	m_skinModel.Initialize(m_skinModelData);

	//���C�g�̐ݒ�B
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_skinModel.SetLight(&m_light);
	m_skinModel.SetHasNormalMap(FALSE);

	//�����t�H�O�̃t���O��ݒ�B
	m_skinModel.SetFogDistFlag(TRUE);
	//�����t�H�O�̃p�����[�^�[��ݒ�B
	m_skinModel.SetFogDistParam(150.0f, 300.0f);
	//�����t�H�O�̃p�����[�^�[��ݒ�B
	m_skinModel.SetFogHeightFlag(FALSE);

	//�e�`�悷��t���O���Z�b�g
	m_skinModel.SetShadowReceiverFlag(TRUE);
	m_skinModel.Update(m_position, m_rotation, m_scale);
	//��������Փ˔��藍�݂̏������B
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����B
	D3DXMATRIX* rootBoneMatrix = m_skinModelData->GetRootBoneWorldMatrix();
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
	static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);
}

//�X�V�B
void Stage::Update()
{
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

// �`��B
void Stage::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowCaster){

	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowCaster);
}
