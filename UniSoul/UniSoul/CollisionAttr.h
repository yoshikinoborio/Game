/*!
 * @brief	コリジョン属性
 */
#pragma once

/*!
 * @brief	コリジョン属性の大分類。
 */
enum EnCollisionAttr{
	enCollisionAttr_Ground,
	enCollisionAttr_Wall,
	enCollisionAttr_Character,
	enCollisionAttr_Respawn,
	enCollisionAttr_User,		//以下にユーザー定義のコリジョン属性を設定する。
};