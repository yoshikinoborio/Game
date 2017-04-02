/*!
 * @brief	コライダー。
 */

#pragma once

/*!
 * @brief	コライダーのインターフェースクラス。
 */
class ICollider {
public:
	virtual btCollisionShape* GetBody() = 0;
	virtual btBoxShape* GetBoxBody() = 0;
};
