#pragma once
#include "2DImage.h"

//�^�C�g���̉摜�\���N���X�B
class Title : public C2DImage
{
public:
	//�R���X�g���N�^�B
	Title();

	//�f�X�g���N�^�B
	~Title();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();
};