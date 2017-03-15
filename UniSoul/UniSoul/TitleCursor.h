#pragma once
#include "2DImage.h"
#include "SoundSource.h"

//�J�[�\�������̈ړ����ł���܂őҋ@���鎞�ԁB
namespace {
	const short CURSOR_MOVEWAITTIME = 200;
}

//�^�C�g���V�[���̃J�[�\���B
class TitleCursor :
	public C2DImage
{
public:
	//�^�C�g���̃��j���[�̎�ށB
	enum class TitleMenu {
		enGameStart = 0,//�Q�[���J�n�B
		enGameEnd,		//�Q�[���I���B
	};

	//�R���X�g���N�^�B
	TitleCursor();

	//�f�X�g���N�^�B
	~TitleCursor();

	//������
	void Initialize();

	//�X�V�B
	void Update();

	//�J�[�\���̈ړ������B
	void MoveCursor();

	//�J�[�\���̈ړ����̍Đ��B
	void MoveCursorSE();

	//�e���j���[�̏����B
	void MenuProcess();
private:
	int				m_nowMenu;			//���ݑI������Ă��郁�j���[���i�[�B
	float			m_lStick_y;			//���X�e�B�b�N��Y���̓��͗ʂ��i�[�B
	DWORD			m_nowTime;			//���݂̎��Ԃ��i�[�B
	DWORD			m_cursorMoveTime;	//�J�[�\���ړ���o�ߎ��ԁB
	CSoundSource	m_cursorMoveSE;		//�J�[�\���̈ړ����B
};