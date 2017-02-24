#pragma once
#include "SkinModelData.h"
#include <map>
class SkinModel;
class Animation;

//���f����ǂݍ���Ŏg���܂킷���ǂ��������߂�N���X�B
class SkinModelDataResources
{
public:
	SkinModelDataResources();
	~SkinModelDataResources();
	/*!
	* @brief	���[�h�B
	*@param[in]	modelPath			���f���̃t�@�C���p�X�B
	*@param[in]	anim				�A�j���[�V�����B
	*/
	SkinModelData* Load(
		const char* modelPath,
		Animation* anim
	);
	/*!
	* @brief	SkinModelData�̃����[�X��j���B
	*/
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