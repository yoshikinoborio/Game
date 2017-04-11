#include "stdafx.h"
#include "Respawn.h"
#include "CollisionAttr.h"
#include "SceneManager.h"

namespace {
	//���X�|�[���n�_�̔z�u���B
	struct RespawnInfo {
		D3DXVECTOR3	pos;			//���W�B
		D3DXQUATERNION	rotation;	//��]�B
		D3DXVECTOR3 scale;			//�X�P�[���B
	};

	//���X�|�[���n�_�̔z�u�e�[�u���B
	RespawnInfo RespawnInfoTable[] = {
#include "RespawnInfo.h"
	};
}

//�R���X�g���N�^�B
Respawn::Respawn()
{
	m_postion = Vector3Zero;
}

//�f�X�g���N�^�B
Respawn::~Respawn()
{
	//�S�[�X�g�I�u�W�F�N�g�̍폜�B
	for (auto ghostobject: m_ghostObjectList)
	{
		delete ghostobject;
	}
}

//�������B
void Respawn::Initialize()
{
	//Unity����o�͂��ꂽ���ł��S�[�X�g�I�u�W�F�N�g�𐶐����鏈���B
	for (RespawnInfo& respawninfo : RespawnInfoTable)
	{
		//���𐶐��B
		btBoxShape* box = new btBoxShape(btVector3(respawninfo.scale.x*0.5f, respawninfo.scale.y*0.5f, respawninfo.scale.z*0.5f));

		//Unity����f���o���ꂽ�ʒu�A��]�A�g������Ɋe�s��̐ݒ�B
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(respawninfo.pos.x, respawninfo.pos.y, respawninfo.pos.z));
		groundTransform.setRotation(btQuaternion(respawninfo.rotation.x, respawninfo.rotation.y, respawninfo.rotation.z, respawninfo.rotation.w));

		//�S�[�X�g�I�u�W�F�N�g�̐����B
		btGhostObject* ghost = new btGhostObject();
		ghost->activate();
		//�S�[�X�g�I�u�W�F�N�g�̌`�𔠂ɂ���B
		ghost->setCollisionShape(box);

		//�e�s��̏����S�[�X�g�I�u�W�F�N�g�ɐݒ�B
		ghost->setWorldTransform(groundTransform);

		//�S�[�X�g�I�u�W�F�N�g�̈ʒu�̃A�h���X��ݒ�B
		ghost->setUserPointer(&respawninfo.pos);

		//������̓��X�|�[���n�_�Ɛݒ�B
		ghost->setUserIndex(enCollisionAttr_Respawn);

		//���X�g�ɒǉ��B
		m_ghostObjectList.push_back(ghost);

		//�������[���h�ɒǉ��B
		static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddGhostObject(ghost);
	}

	m_pEmitter = CParticleEmitter::EmitterCreate(
		"ParticleEmitterStart",
		ParicleType::Star,
		static_cast<GameScene*>(g_pScenes)->GetFileOperation()->ReadText());
	
}

//�X�V�B
void Respawn::Update()
{
	m_pEmitter->SetEmitPos(static_cast<GameScene*>(g_pScenes)->GetFileOperation()->ReadText());
	m_pEmitter->Update();
}

//�`��B
void Respawn::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver) 
{
	m_pEmitter->Render(&viewMatrix, &projMatrix);
}