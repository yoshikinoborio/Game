#pragma once
#include "SkinModel.h"
#include "Turn.h"
#include "RigidBody.h"
#include "MeshCollider.h"
#include "DamageCollisionWorld.h"

//�A�j���[�V��������3D���f���̊��N���X�B
class AnimationModel3D
{
public:
	AnimationModel3D();
	//�f�X�g���N�^��Virtua��t���闝�R��
	//�h���N���X�̃f�X�g���N�^���Ă΂ꂸ���������[�N���N���邩��t���Ă���B
	virtual~AnimationModel3D() 
	{
	}
	//�������z�֐��͂�����N���X���̃��\�b�h��h���N���X���ŕK������(��`)���Ă��炢�����ꍇ�A�������z�֐��Ő錾����B
	//�������z�֐��Ő錾���ꂽ�N���X���p������ꍇ�A�K���I�[�o�[���C�h���Ȃ���΂Ȃ�Ȃ��B
	//���N���X�̃����o���\�b�h���p���N���X�ŕύX���鎖���ł���B�ȒP�Ɍ����΁A�Ē�`����Ƃ������B
	//���̊��N���X�̊֐�(�I�[�o�[���C�h�����֐�)�����z�֐��ƌ����B
	virtual void Update() = 0;
protected:
	SkinModelData*	m_skinModelData;					//�X�L�����f���f�[�^�B
	SkinModel		m_skinModel;						//�X�L�����f���B
	Animation		m_animation;						//�A�j���[�V�����B
	Turn			m_turn;								//��]�B
	MeshCollider	m_meshCollider;						//���b�V���R���C�_�[�B
	RigidBody		m_rigidBody;						//���́B
};