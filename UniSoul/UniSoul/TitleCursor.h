#pragma once
#include "2DImage.h"
#include "SoundSource.h"

#define CURSOR_MOVETIME 200


//�^�C�g���̃��j���[�̎�ށB
enum TitleMenu {
	enGameStart = 0,//�Q�[���J�n�B
	enGameEnd,		//�Q�[���I���B
};

//�^�C�g���V�[���̃J�[�\���B
class TitleCursor :
	public C2DImage
{
public:
	TitleCursor();
	~TitleCursor();
	//������
	void Initialize();
	//�X�V�B
	void Update();
	//�J�[�\���̈ړ������B
	void MoveCursor();
private:
	short			m_nowMenu;			//���ݑI������Ă��郁�j���[���i�[�B
	float			m_lStick_y;			//���X�e�B�b�N��Y���̓��͗ʂ��i�[�B
	DWORD			m_nowTime;			//���݂̎��Ԃ��i�[�B
	DWORD			m_cursorMoveTime;	// �J�[�\���ړ���o�ߎ��ԁB
	CSoundSource	m_cursorMoveSE;		//�J�[�\���̈ړ����B
};