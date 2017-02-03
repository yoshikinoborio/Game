#pragma once
#include "stdafx.h"

/*!
* @brief	�p�[�e�B�N�������p�����[�^�B
*/
//�p�[�e�B�N�������p�����[�^�\���̂̒�`�B
struct SParicleEmitParameter {
	//�������B
	void Init()
	{
		memset(this, 0, sizeof(SParicleEmitParameter));
	}
	const char* texturePath;			//!<�e�N�X�`���̃t�@�C���p�X�B
	float w;							//!<�p�[�e�B�N���̕��B
	float h;							//!<�p�[�e�B�N���̍����B
	float intervalTime;					//!<�p�[�e�B�N���̔����Ԋu�B
	D3DXVECTOR3 initSpeed;				//!<�����x�B
	D3DXVECTOR3 position;				//!<�����ʒu�B
	float	life;						//!<�p�[�e�B�N���̐������ԁB
};

enum ParicleType {
	Star = 0
};

//���B
static SParicleEmitParameter Star_Paricle = {
	"image\\star.png",				//!<�e�N�X�`���̃t�@�C���p�X�B
	0.5f,							//!<�p�[�e�B�N���̕��B
	0.5f,							//!<�p�[�e�B�N���̍����B
	0.01f,							//!<�p�[�e�B�N���̔����Ԋu�B
	D3DXVECTOR3(0.0f,1.0f,0.0f),	//!<�����x�B
	D3DXVECTOR3(0.0f,0.0f,0.0f),	//!<�ʒu�B
	1.0f							//!<�p�[�e�B�N���̐������ԁB
};

static SParicleEmitParameter* ParticleParamPT_Array[] = {
	&Star_Paricle
};