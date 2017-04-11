#include "stdafx.h"
#include "CollisionCreat.h"
#include "SceneManager.h"
#include "CollisionAttr.h"

namespace {
	//�����Ȃ������蔻��̔z�u���B
	struct CollsionInfo {
		D3DXVECTOR3	pos;			//���W�B
		D3DXQUATERNION	rot;	//��]�B
		D3DXVECTOR3 scale;			//�X�P�[���B
	};
	//�����Ȃ������蔻��̔z�u���̃e�[�u���B
	CollsionInfo CollsionInfoTable[] = {
#include "CollisionInfo.h"
	};
}

//�R���X�g���N�^�B
CollisionCreat::CollisionCreat()
{

}

//�f�X�g���N�^�B
CollisionCreat::~CollisionCreat()
{
	//�S�[�X�g�I�u�W�F�N�g�̍폜�B
	for (auto ghostobject : m_ghostObjectList)
	{
		delete ghostobject;
	}
}

//�������B
void CollisionCreat::Initialize()
{
	for (CollsionInfo& CollInfo : CollsionInfoTable) {
		//�S�[�X�g�I�u�W�F�N�g���������B

		btBoxShape* box = new btBoxShape(btVector3(CollInfo.scale.x*0.5f, CollInfo.scale.y*0.5f, CollInfo.scale.z*0.5f));

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(CollInfo.pos.x, CollInfo.pos.y, CollInfo.pos.z));
		groundTransform.setRotation(btQuaternion(CollInfo.rot.x, CollInfo.rot.y, CollInfo.rot.z, CollInfo.rot.w));

		//�S�[�X�g�I�u�W�F�N�g�̐����B
		btGhostObject* ghost = new btGhostObject();
		ghost->activate();
		//�S�[�X�g�I�u�W�F�N�g�̌`�𔠂ɂ���B
		ghost->setCollisionShape(box);

		//�e�s��̏����S�[�X�g�I�u�W�F�N�g�ɐݒ�B
		ghost->setWorldTransform(groundTransform);

		//������̓��X�|�[���n�_�Ɛݒ�B
		ghost->setUserIndex(enCollisionAttr_Wall);

		//���X�g�ɒǉ��B
		m_ghostObjectList.push_back(ghost);

		//�������[���h�ɒǉ��B
		static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddGhostObject(ghost);
	}
}