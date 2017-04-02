/*!
 * @brief	カプセルコライダー。
 */

#pragma once

#include "ICollider.h"

class CapsuleCollider : public ICollider
{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	CapsuleCollider();
	/*!
	 * @brief	デストラクタ。
	 */
	~CapsuleCollider();
	/*!
	* @brief	作成。
	*/
	void Create(float radius, float height)
	{
		shape = new btCapsuleShape(radius, height);
	}
	btCollisionShape* GetBody() override
	{
		return shape;
	}

	//Box作成。
	void CreateBox(const D3DXVECTOR3& size)
	{
		box = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
	}

	btBoxShape* GetBoxBody() override
	{
		return box;
	}
private:
	btCapsuleShape*		shape;
	btBoxShape*			box;
};
