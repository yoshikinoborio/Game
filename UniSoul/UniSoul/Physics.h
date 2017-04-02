#pragma once


class RigidBody;

/*!
 * @brief	物理ワールド。
 */
class PhysicsWorld
{
	btDefaultCollisionConfiguration*		collisionConfig;
	btCollisionDispatcher*					collisionDispatcher;	//!<衝突解決処理。
	btBroadphaseInterface*					overlappingPairCache;	//!<ブロードフェーズ。衝突判定の枝切り。
	btSequentialImpulseConstraintSolver*	constraintSolver;		//!<コンストレイントソルバー。拘束条件の解決処理。
	btDiscreteDynamicsWorld*				dynamicWorld;			//!<ワールド。
public:
	PhysicsWorld();
	~PhysicsWorld();
	void Initialize();
	void Release();
	void Update() ;
	/*!
	* @brief	ダイナミックワールドを取得。
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}

	//剛体の追加。
	void AddRigidBody(RigidBody* rb);

	//剛体の削除。
	void RemoveRigidBody(RigidBody* rb);

	//ゴーストオブジェクトの追加。
	void AddGhostObject(btGhostObject* ghost);

	//ゴーストオブジェクトの削除。
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

