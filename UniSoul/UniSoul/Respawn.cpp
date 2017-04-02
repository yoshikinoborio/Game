#include "stdafx.h"
#include "Respawn.h"
#include "CollisionAttr.h"
#include "SceneManager.h"

Respawn::Respawn()
{
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(50.0f, -5.0f, 50.0f);
	m_size = Vector3One;
	m_ghostObject = NULL;
	m_GhostShape = NULL;
}


Respawn::~Respawn()
{
	delete m_ghostObject;
	delete m_GhostShape;
	m_ghostObject = NULL;
	m_GhostShape = NULL;
}

void Respawn::Initialize()
{
	//m_size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	//m_characterController.GhostObjecInitialize(m_position, m_size, m_rotation, 10.0f, 10.0f);
	//m_characterController.SetGravity(0.0f);
	m_size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	m_GhostShape = new btBoxShape(btVector3(m_size.x*0.5f, m_size.y*0.5f, m_size.z*0.5f));
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	groundTransform.setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));

	m_ghostObject = new btGhostObject();
	m_ghostObject->activate();
	m_ghostObject->setCollisionShape(m_GhostShape);
	m_ghostObject->setWorldTransform(groundTransform);
	m_ghostObject->setUserPointer(&m_position);
	m_ghostObject->setUserIndex(enCollisionAttr_Respawn);

	static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddGhostObject(m_ghostObject);
}

void Respawn::Update()
{

}