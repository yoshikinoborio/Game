#pragma once

//�o�C�i���t�@�C���̓��o�͂��s���N���X�B
class FileOperation
{
public:
	//�R���X�g���N�^�B
	FileOperation();

	//�f�X�g���N�^�B
	~FileOperation();

	//�o�C�i���t�@�C���ɓf���o�������B
	void OutPutText(const D3DXVECTOR3& pos);

	//�o�C�i���t�@�C����������擾���鏈���B
	const D3DXVECTOR3& ReadText() const;
};