#pragma once


class RigidBody;

/*!
 * @brief	�������[���h�B
 */
class PhysicsWorld
{
	btDefaultCollisionConfiguration*		collisionConfig;
	btCollisionDispatcher*					collisionDispatcher;	//!<�Փˉ��������B
	btBroadphaseInterface*					overlappingPairCache;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	btSequentialImpulseConstraintSolver*	constraintSolver;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
	btDiscreteDynamicsWorld*				dynamicWorld;			//!<���[���h�B
public:
	PhysicsWorld();
	~PhysicsWorld();
	void Initialize();
	void Release();
	void Update() ;
	/*!
	* @brief	�_�C�i�~�b�N���[���h���擾�B
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}

	//���̂̒ǉ��B
	void AddRigidBody(RigidBody* rb);

	//���̂̍폜�B
	void RemoveRigidBody(RigidBody* rb);

	//�S�[�X�g�I�u�W�F�N�g�̒ǉ��B
	void AddGhostObject(btGhostObject* ghost);

	//�S�[�X�g�I�u�W�F�N�g�̍폜�B
	void RemoveGhostObject(btGhostObject* ghost);

	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
		)
	{
		dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
};

