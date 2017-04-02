#include "stdafx.h"
#include "FileOperation.h"
#include <fstream>
using namespace std;

//�v���C���[���Ō�ɃZ�[�u�����ʒu���i�[����B
namespace {
	struct PlayerDateInfo
	{
		D3DXVECTOR3 pos = { 100.0f,100.0f,100.0f };	//�v���C���[���Ō�ɓ��B�����Z�[�u�|�C���g�B
	}SaveDate;
}

//�R���X�g���N�^�B
FileOperation::FileOperation()
{
}

//�f�X�g���N�^�B
FileOperation::~FileOperation()
{
}

//�o�C�i���t�@�C���ɓf���o�������B
void FileOperation::OutPutText(const D3DXVECTOR3& pos)
{
	SaveDate.pos = pos;

	//�ǂݍ��ރt�@�C���Ƒ��삷�郂�[�h���w��B
	FILE *fp = fopen("PlayerRespawnPosition.dat", "wb");//�o�C�i���t�@�C�����J���B
	if (fp == NULL) {//�G���[���N������NULL��Ԃ��B
		OutputDebugString("�t�@�C�����ǂݍ��߂Ȃ������B");
	}
	else
	{
		//���������A�Z�[�u�f�[�^���������ϐ��̃A�h���X�B
		//���������A�o�͂���o�C�g���B
		//��O�������A�o�͂�����B
		//��l�������A�o�͂���t�@�C���|�C���^�B
		fwrite(&SaveDate, sizeof(SaveDate), 1, fp); // SaveData�\���̂̒��g���o�́B
		fclose(fp);//�t�@�C�������B
	}

}

//�o�C�i���t�@�C����������擾���鏈���B
const D3DXVECTOR3& FileOperation::ReadText() const
{
	//�ǂݍ��ރt�@�C���Ƒ��삷�郂�[�h���w��B
	FILE *fp = fopen("PlayerRespawnPosition.dat", "rb");//�o�C�i���t�@�C�����J���B
	if (fp == NULL) {
		OutputDebugString("�t�@�C�����ǂݍ��߂Ȃ������B");
	}
	else
	{
		//�o�C�i���ɓf���o��������ǂݍ��ށB
		fread(&SaveDate, sizeof(SaveDate), 1, fp);
		fclose(fp);
		return SaveDate.pos;
	}
	
}
