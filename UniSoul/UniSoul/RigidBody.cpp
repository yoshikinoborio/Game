#include "stdafx.h"
#include "RigidBody.h"
#include "ICollider.h"

RigidBody::RigidBody() :
	rigidBody(NULL),
	myMotionState(NULL)
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
	rigidBody = NULL;
	myMotionState = NULL;
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
	//çÑëÃÇçÏê¨ÅB
	rigidBody = new btRigidBody(btRbInfo);
}

void RigidBody::CreateBox(RigidBodyBoxInfo& rbInfo)
{
	Release();
	btBoxShape* box = new btBoxShape(btVector3(rbInfo.scale.x*0.5f, rbInfo.scale.y*0.5f, rbInfo.scale.z*0.5f));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w));
	myMotionState = new btDefaultMotionState;
	btRigidBody::btRigidBodyConstructionInfo btRbInfo(rbInfo.mass, myMotionState, box, btVector3(0, 0, 0));
	//çÑëÃÇçÏê¨ÅB
	rigidBody = new btRigidBody(btRbInfo);
}