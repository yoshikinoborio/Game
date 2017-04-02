#include "stdafx.h"
#include "RigidBody.h"
#include "ICollider.h"

RigidBody::RigidBody() :
	rigidBody(NULL),
	myMotionState(NULL),
	ghostObject(NULL)
{
}


RigidBody::~RigidBody()
{
	Release();
}
void RigidBody::Release()
{
	delete rigidBody;
	delete myMotionState;
	delete ghostObject;
	rigidBody = NULL;
	myMotionState = NULL;
	ghostObject = NULL;
}
void RigidBody::Create(RigidBodyInfo& rbInfo)
{
	Release();
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w));
	myMotionState = new btDefaultMotionState;
	btRigidBody::btRigidBodyConstructionInfo btRbInfo(rbInfo.mass, myMotionState, rbInfo.collider->GetBody(), btVector3(0, 0, 0));
	//„‘Ì‚ðì¬B
	rigidBody = new btRigidBody(btRbInfo);
}

void RigidBody::CreateGhostObject(GhostObjectInfo& rbInfo)
{
	Release();
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	Transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w));

	ghostObject = new btGhostObject();
	ghostObject->activate();
	ghostObject->setCollisionShape(rbInfo.collider->GetBoxBody());
	ghostObject->setWorldTransform(Transform);
}