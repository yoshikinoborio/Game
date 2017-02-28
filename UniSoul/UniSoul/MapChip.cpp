#include "stdafx.h"
#include "MapChip.h"
#include "SceneManager.h"

MapChip::MapChip()
{
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_drawFlag = FALSE;
}

MapChip::~MapChip()
{

}

void MapChip::Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation)
{
	m_position = pos;
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rotation = rotation;

	//���f�������[�h�B
	m_skinModelData = static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load(modelPath, &m_animation);
	//m_skinModelDataResources.Load(modelPath, &m_animation);
	//m_skinModelData.LoadModelData(modelPath, &m_animation);
	m_skinModel.Initialize(m_skinModelData);

	//���C�g�̐ݒ�B
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	m_skinModel.SetLight(&m_light);

	m_skinModel.SetHasNormalMap(FALSE);

	//�����t�H�O�̃t���O��ݒ�B
	m_skinModel.SetFogDistFlag(TRUE);
	//�����t�H�O�̃p�����[�^�[��ݒ�B
	m_skinModel.SetFogDistParam(150.0f, 300.0f);
	//�����t�H�O�̃t���O��ݒ�B
	m_skinModel.SetFogHeightFlag(FALSE);


	m_skinModel.Update(pos, rotation, { 1.0f, 1.0f, 1.0f });
	D3DXMATRIX m_world;
	//��������Փ˔��藍�݂̏������B
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����B
	D3DXMATRIX* rootBoneMatrix = m_skinModelData->GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_skinModel, rootBoneMatrix);
	//�����č��̂��쐬����B
	//�܂��͍��̂��쐬���邽�߂̏���ݒ�B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;	//���̂̃R���W������ݒ肷��B
	rbInfo.mass = 0.0f;					//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
	rbInfo.pos = pos;
	rbInfo.rot = rotation;
	//���̂��쐬�B
	m_rigidBody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);

}

void MapChip::Update()
{
	//if (m_drawFlag == FALSE)
	//{
		//�}�b�v�I�u�W�F�N�g���X�V�B
		m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f,1.0f });
		m_drawFlag = TRUE;
	//}
	
}

void MapChip::Draw(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	//�}�b�v�I�u�W�F�N�g��`��B
	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowReceiver);
}