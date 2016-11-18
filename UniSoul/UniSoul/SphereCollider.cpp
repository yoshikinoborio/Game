/*!
* @brief	���̃R���C�_�[�B
*/

#include "stdafx.h"
#include "SphereCollider.h"


	/*!
	* @brief	�R���X�g���N�^�B
	*/
	CSphereCollider::CSphereCollider() :
		shape(NULL)
	{
	}
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	CSphereCollider::~CSphereCollider()
	{
		delete shape;
	}
	/*!
	* @brief	���̃R���C�_�[���쐬�B
	*/
	void CSphereCollider::Create(const float radius)
	{
		shape = new btSphereShape(radius);
	}
