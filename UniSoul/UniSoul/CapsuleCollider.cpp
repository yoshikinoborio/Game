/*!
 * @brief	カプセルコライダー。
 */

#include "stdafx.h"
#include "CapsuleCollider.h"

/*!
 * @brief	コンストラクタ。
 */
CapsuleCollider::CapsuleCollider() :
	shape(nullptr)
{
}
/*!
 * @brief	デストラクタ。
 */
CapsuleCollider::~CapsuleCollider()
{
	delete shape;
}
