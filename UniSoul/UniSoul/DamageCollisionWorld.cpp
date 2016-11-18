/*!
* @brief	敵、プレイヤーにダメージを与えるコリジョンワールド。
*/

#include "stdafx.h"
#include "DamageCollisionWorld.h"

namespace {
	struct MyContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
		MyContactResultCallback()
		{

		}
		btCollisionObject* queryCollisionObject = nullptr;
		DamageCollisionWorld::Collision* hitObject = nullptr;
		float distSq = FLT_MAX;
		DamageCollisionWorld::EnAttr queryAttr = DamageCollisionWorld::enDamageToEnemy;	//調べるコリジョン属性。
		virtual	btScalar	addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override
		{
			const D3DXVECTOR3* vColl0Pos = (D3DXVECTOR3*)(&colObj0Wrap->getWorldTransform().getOrigin());
			const D3DXVECTOR3* vColl1Pos = (D3DXVECTOR3*)(&colObj1Wrap->getWorldTransform().getOrigin());
			D3DXVECTOR3 vDist;
			//vDist.Subtract(*vColl0Pos, *vColl1Pos);
			vDist = *vColl0Pos - *vColl1Pos;
			//float distTmpSq = vDist.LengthSq();
			float distTmpSq = D3DXVec3LengthSq(&vDist);
			DamageCollisionWorld::Collision* hitObjectTmp;
			if (distTmpSq < distSq) {
				//こちらの方が近い。
				if (queryCollisionObject == colObj0Wrap->getCollisionObject()) {
					hitObjectTmp = (DamageCollisionWorld::Collision*)colObj1Wrap->getCollisionObject()->getUserPointer();
				}
				else {
					hitObjectTmp = (DamageCollisionWorld::Collision*)colObj0Wrap->getCollisionObject()->getUserPointer();
				}
				if (hitObjectTmp->attr == queryAttr) {
					distSq = distTmpSq;
					hitObject = hitObjectTmp;
				}
			}

			return 0.0f;
		}
	};
}
DamageCollisionWorld::DamageCollisionWorld()
{
}

DamageCollisionWorld::~DamageCollisionWorld()
{
}
void DamageCollisionWorld::Start()
{
	collisionConfig.reset(new btDefaultCollisionConfiguration);
	collisionDispatcher.reset(new btCollisionDispatcher(collisionConfig.get()));
	overlappingPairCache.reset(new btDbvtBroadphase());
	collisionWorld.reset(new btCollisionWorld(collisionDispatcher.get(), overlappingPairCache.get(), collisionConfig.get()));
}
/*!
*@brief	ダメージコリジョンと重なっているか調べる。
*/
const DamageCollisionWorld::Collision* DamageCollisionWorld::FindOverlappedDamageCollision(EnAttr attr, const D3DXVECTOR3& pos, float radius) const
{
	for (auto& collision : collisions) {
		if (collision->attr == attr) {
			float t = collision->radius + radius;
			D3DXVECTOR3 diff;
			//diff.Subtract(collision->position, pos);
			diff = collision->position - pos;
			//if (diff.LengthSq() < t * t) {
			//	//当たった。
			//	return collision.get();
			//}
			if (D3DXVec3LengthSq(&diff) < t * t) {
				//当たった。
				return collision.get();
			}
		}
	}
	return nullptr;
}
const DamageCollisionWorld::Collision* DamageCollisionWorld::FindOverlappedDamageCollision(EnAttr attr, btCollisionObject* colliObject) const
{
	MyContactResultCallback callback;
	callback.queryCollisionObject = colliObject;
	callback.queryAttr = attr;
	collisionWorld->contactTest(colliObject, callback);

	return callback.hitObject;
}
void DamageCollisionWorld::Update()
{
	std::list<CollisionPtr>::iterator it = collisions.begin();
	while (it != collisions.end()) {
		(*it)->time += DeltaTime;
		if ((*it)->time > (*it)->life) {
			//死亡。
			collisionWorld->removeCollisionObject((*it)->collisionObject.get());
			it = collisions.erase(it);
		}
		else {
			it++;
		}
	}
	collisionWorld->updateAabbs();
}