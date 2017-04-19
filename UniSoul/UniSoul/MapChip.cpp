#include "stdafx.h"
#include "MapChip.h"
#include "SceneManager.h"

//�R���X�g���N�^�B
MapChip::MapChip()
{
	m_position = Vector3Zero;
	m_scale = Vector3Zero;
}

//�f�X�g���N�^�B
MapChip::~MapChip()
{
	delete m_skinModelData;
}

//�������B
void MapChip::Initialize(const char* modelPath, const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation)
{
	m_position = pos;
	m_scale = Vector3One;
	m_rotation = rotation;

	//���f�������[�h�B
	m_skinModelData = static_cast<GameScene*>(g_pScenes)->GetSkinModelDataResources()->Load(modelPath, &m_animation);
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

	m_light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	m_skinModel.SetLight(&m_light);

	m_skinModel.SetHasNormalMap(FALSE);

	//�����t�H�O�̃t���O��ݒ�B
	m_skinModel.SetFogDistFlag(TRUE);
	//�����t�H�O�̃p�����[�^�[��ݒ�B
	m_skinModel.SetFogDistParam(150.0f, 300.0f);
	//�����t�H�O�̃t���O��ݒ�B
	m_skinModel.SetFogHeightFlag(FALSE);


	m_skinModel.Update(pos, rotation, m_scale);
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
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	//���̂��쐬�B
	m_rigidBody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);
}

//�X�V�B
void MapChip::Update()
{
	//�}�b�v�I�u�W�F�N�g���X�V�B
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

//�`��B
void MapChip::Draw(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowCaster)
{
	//�}�b�v�I�u�W�F�N�g��`��B
	m_skinModel.Draw(&viewMatrix, &projMatrix, isShadowCaster);
}