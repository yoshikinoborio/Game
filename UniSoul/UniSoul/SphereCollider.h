/*!
* @brief	球体コライダー。
*/
#pragma once
#include "ICollider.h"

class CSphereCollider : public ICollider
{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	CSphereCollider();
	/*!
	* @brief	デストラクタ。
	*/
	~CSphereCollider();
	/*!
	* @brief	球体コライダーを作成。
	*/
	void Create(const float radius);
	btCollisionShape* GetBody() override
	{
		return shape;
	}
	btBoxShape* GetBoxBody() override
	{
		return box;
	}
private:
	btSphereShape*		shape;
	btBoxShape*			box;
};