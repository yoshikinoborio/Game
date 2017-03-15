#pragma once
#include "SkinModelData.h"
#include <map>
class SkinModel;
class Animation;

//���f����ǂݍ���Ŏg���܂킷���ǂ��������߂�N���X�B
class SkinModelDataResources
{
public:
	//�R���X�g���N�^�B
	SkinModelDataResources();

	//�f�X�g���N�^�B
	~SkinModelDataResources();


	//���f���̃��[�h�B
	//���f���̃t�@�C���p�X�B
	//�A�j���[�V�����B
	SkinModelData* Load(
		const char* modelPath,
		Animation* anim
	);
	
	//SkinModelData�̃����[�X��j���B
	void Release();
	///*!
	//* @brief	�K�x�[�W�R���N�g�̎��s�B
	//*@details
	//* �Q�ƃJ�E���^���ɂȂ��Ă���CSkinModelData���������܂��B
	//*/
	//void GC();
private:
	std::map<int, SkinModelData*> m_SkinModelDataList;	//�X�L�����f���f�[�^�̃��X�g�B
};