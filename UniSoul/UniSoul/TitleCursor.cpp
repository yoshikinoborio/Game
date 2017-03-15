#include "stdafx.h"
#include "TitleCursor.h"
#include "SceneManager.h"

//�e���j���[�̈ʒu���B
//������X�^�[�g�A�I���B
namespace {
	const D3DXVECTOR2  MenuPostion[2] = { { 820.0f, 265.0f },{820.0f, 320.0f} };
}

//�R���X�g���N�^�B
TitleCursor::TitleCursor()
{
	//�J�[�\�����Q�[���X�^�[�g�̈ʒu����J�n�B
	m_nowMenu = (int)TitleMenu::enGameStart;
	//�e�ϐ��̏������B
	m_lStick_y = 0.0f;
	m_position = Vector2Zero;
	m_angle = 0;
	m_scale = Vector2Zero;
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
	m_cursorMoveTime = 0;
}

//�f�X�g���N�^�B
TitleCursor::~TitleCursor()
{
}


//�������B
void TitleCursor::Initialize()
{
	m_position = MenuPostion[m_nowMenu];
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.0f, 1.0f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\UniSoul_Cursor.png";
	C2DImage::Initialize();
	//�J�[�\���̈ړ�����SE�̏������B
	m_cursorMoveSE.Init("image/UniSoul_CursorMoveSE.wav");
}


//�X�V�B
void TitleCursor::Update()
{
	//�J�[�\���̈ړ������B
	MoveCursor();
	
	//�e���j���[�̏����B
	MenuProcess();
	
	//�J�[�\���̈ړ�����SE�̍X�V�B
	m_cursorMoveSE.Update();

	this->SetupMatrices();
}


//�e���j���[�̏����B
void TitleCursor::MenuProcess()
{
	//�I������Ă��郁�j���[�̏�Ԃ����ď�����ύX�B
	switch (m_nowMenu)
	{
		//�Q�[���X�^�[�g�B
	case (int)TitleMenu::enGameStart:
		if (g_pad.IsTrigger(enButtonA))
		{
			g_sceneManager->ChangeScene(2);
		}
		break;
		//�Q�[���I���B
	case (int)TitleMenu::enGameEnd:
		if (g_pad.IsTrigger(enButtonA))
		{
			PostQuitMessage(0);
		}
		break;
	default:
		break;
	}
}

//�J�[�\���̈ړ����̍Đ��B
void TitleCursor::MoveCursorSE()
{
	//�ړ������Đ��B
	m_cursorMoveSE.Play(FALSE);
	m_cursorMoveSE.SetVolume(0.25f);
}

//�J�[�\���̈ړ������B
void TitleCursor::MoveCursor()
{
	//���X�e�B�b�NY���̓��͗ʂ��i�[�B
	m_lStick_y = g_pad.GetLStickYF();
	//���݂̎��Ԃ̎擾�B
	m_nowTime = timeGetTime();
	//�J�[�\���̉��ւ̈ړ��B
	if (m_lStick_y < 0.0f) {
		//��莞�Ԓ����Ȃ��ƃJ�[�\���͓����Ȃ��B
		if (m_nowTime - m_cursorMoveTime > CURSOR_MOVEWAITTIME) {
			m_cursorMoveTime = m_nowTime;

			//�I�����郁�j���[���������B
			m_nowMenu += 1;
			//���������ʂ����j���[�̍Ō�����l���傫���Ȃ��ԏ�̃��j���[�Ɉړ�������B
			if (m_nowMenu > (int)TitleMenu::enGameEnd)
			{
				m_nowMenu = (int)TitleMenu::enGameStart;
			}

			//�ړ������Đ��B
			MoveCursorSE();
		}
	}

	//�J�[�\���̏�ւ̈ړ��B
	if (m_lStick_y > 0.0f) {
		//��莞�Ԓ����Ȃ��ƃJ�[�\���͓����Ȃ��B
		if (m_nowTime - m_cursorMoveTime > CURSOR_MOVEWAITTIME) {
			m_cursorMoveTime = m_nowTime;

			//�I�����郁�j���[����グ��B
			m_nowMenu -= 1;
			//���������ʂ����j���[�̍ŏ������l���������Ȃ��ԉ��̃��j���[�Ɉړ�������B
			if (m_nowMenu < (int)TitleMenu::enGameStart)
			{
				m_nowMenu = (int)TitleMenu::enGameEnd;
			}
			//�ړ������Đ��B
			MoveCursorSE();
		}
	}

	//���X�e�B�b�N��Y�����������͂���Ă��Ȃ��Ȃ�J�[�\���̈ړ����Ԃ��N���A�B
	if (m_lStick_y == 0.0f)
	{
		m_cursorMoveTime = 0;
	}

	//�I������Ă��郁�j���[�����ăJ�[�\���̈ʒu���X�V�B
	m_position = MenuPostion[m_nowMenu];

}