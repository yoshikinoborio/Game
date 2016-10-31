#pragma once
#include "PreCompile.h"
class Effect;

//�G�t�F�N�g�}�l�[�W���B
class EffectManager{
public:
	//�R���X�g���N�^
	EffectManager();
	//�f�X�g���N�^
	~EffectManager();
	/*!
	*@brief	�G�t�F�N�g�̃��[�h�B
	*@details
	* �ǂݍ��ݍς݂̃G�t�F�N�g�̏ꍇ�̓��[�h�͍s��ꂸ�A</br>
	* �����̃G�t�F�N�g���Ԃ��Ă���
	*@param[in]	filePath	���[�h����G�t�F�N�g�̃t�@�C���p�X�B
	*@return	���[�h�����G�t�F�N�g�t�@�C���B
	*/
	ID3DXEffect* LoadEffect(const char* filePath);
	//���
	void Release();
private:
	//map�̓��j�[�N�ȗv�f���i�[����A�z�R���e�i�̈��ł���A�L�[�Ƃ���ɑΉ�����l���i�[(�݂��ɓ�������̃L�[�����v�f��map�Ɋi�[����邱�Ƃ͖���)
	std::map<int, ID3DXEffect*>		m_effectDictinary;	//CEffect�̃C���X�^���X�̃f�B�N�V���i���B�t�@�C���p�X�̃n�b�V���l���L�[�Ɏ����ACEffect�̃C���X�^���X��l�Ɏ��B
};
