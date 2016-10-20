#pragma once
#include "SkinModel.h"

//�A�j���[�V��������3D���f���̊��N���X�B
class AnimationModel3D
{
public:
	AnimationModel3D();
	~AnimationModel3D();
	//�������z�֐��͂�����N���X���̃��\�b�h��h���N���X���ŕK������(��`)���Ă��炢�����ꍇ�A�������z�֐��Ő錾����B
	//�������z�֐��Ő錾���ꂽ�N���X���p������ꍇ�A�K���I�[�o�[���C�h���Ȃ���΂Ȃ�Ȃ��B
	//���N���X�̃����o���\�b�h���p���N���X�ŕύX���鎖���ł���B�ȒP�Ɍ����΁A�Ē�`����Ƃ������B
	//���̊��N���X�̊֐�(�I�[�o�[���C�h�����֐�)�����z�֐��ƌ����B
	virtual void Initialize() = 0;
	virtual void Update() = 0;
protected:
	SkinModelData	m_skinModelData;	//�X�L�����f���f�[�^�B
	SkinModel		m_skinModel;		//�X�L�����f���B
	Animation		m_animation;		//�A�j���[�V�����B
};