#include "stdafx.h"
#include "CollisionCreat.h"
#include "SceneManager.h"
#include "CollisionAttr.h"

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
CollsionInfo CollsionInfoTable[] = {
#include "CollisionInfo.h"
};


CollisionCreat::CollisionCreat()
{
}


CollisionCreat::~CollisionCreat()
{

}

void CollisionCreat::Initialize()
{
	for (CollsionInfo& CollInfo : CollsionInfoTable) {
		//���̂��������B
		{
			btBoxShape* work = new btBoxShape(btVector3(CollInfo.scale.x*0.5f, CollInfo.scale.y*0.5f, CollInfo.scale.z*0.5f));
			m_cllisionShape.push_back(work);
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(-CollInfo.pos.x, CollInfo.pos.y, -CollInfo.pos.z));
			groundTransform.setRotation(btQuaternion(-CollInfo.rotation.x, CollInfo.rotation.y, -CollInfo.rotation.z, CollInfo.rotation.w));
			float mass = 0.0f;

			//�쐬�������̂𕨗����[���h�ɒǉ��B
			static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);

			////�����č��̂��쐬����B
			////�܂��͍��̂��쐬���邽�߂̏���ݒ�B
			//RigidBodyInfo rbInfo;
			//rbInfo.mass = 0.0f;					//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
			//rbInfo.pos = CollInfo.pos;
			//rbInfo.rot = CollInfo.rotation;
			////���̂��쐬�B
			//m_rigidBody.Create(rbInfo);
			////�쐬�������̂𕨗����[���h�ɒǉ��B
			//static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);

		}
	}
}