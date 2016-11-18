/*!
* @brief	球体コライダー。
*/

#include "stdafx.h"
#include "SphereCollider.h"


	/*!
	* @brief	コンストラクタ。
	*/
	CSphereCollider::CSphereCollider() :
		shape(NULL)
	{
	}
	/*!
	* @brief	デストラクタ。
	*/
	CSphereCollider::~CSphereCollider()
	{
		delete shape;
	}
	/*!
	* @brief	球体コライダーを作成。
	*/
	void CSphereCollider::Create(const float radius)
	{
		shape = new btSphereShape(radius);
	}
