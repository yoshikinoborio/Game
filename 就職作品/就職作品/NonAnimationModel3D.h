#pragma once
#include "Model3D.h"

//�A�j���[�V�������Ȃ�3D���f���̊��N���X
class NonAnimationModel3D
{
public:
	NonAnimationModel3D();
	~NonAnimationModel3D();
	//�������z�֐�
	virtual void Initialize() = 0;
	//�������z�֐�
	virtual void Update() = 0;
protected:
	Model3D	m_model3d;	//�A�j���[�V�������Ȃ�3D�֌W��\������Model3D�̃C���X�^���X��ێ�
};