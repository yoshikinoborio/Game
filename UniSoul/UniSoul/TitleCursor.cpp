#include "stdafx.h"
#include "TitleCursor.h"
#include "SceneManager.h"

//�e���j���[�̈ʒu���B
//������X�^�[�g�A�I���B
const D3DXVECTOR2  CursorPostion[2] = { { 820.0f, 265.0f },{820.0f, 320.0f} };


TitleCursor::TitleCursor()
{
	//�J�[�\�����Q�[���X�^�[�g�̈ʒu����J�n�B
	m_nowMenu = TitleMenu::enGameStart;
	//�e�ϐ��̏������B
	m_lStick_y = 0.0f;
	m_position = D3DXVECTOR2(0.0f,0.0f);
	m_angle = 0;
	m_scale = D3DXVECTOR2(0.0f, 0.0f);
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
	m_cursorMoveTime = 0;
}


TitleCursor::~TitleCursor()
{
}

void TitleCursor::Initialize()
{
	m_position = D3DXVECTOR2(820.0f, 320.0f);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.0f, 1.0f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\UniSoul_Cursor.png";
	C2DImage::Initialize();
	//�J�[�\���̈ړ�����SE�̏������B
	m_cursorMoveSE.Init("image/UniSoul_CursorMoveSE.wav");
}

void TitleCursor::Update()
{
	//���X�e�B�b�NY���̓��͗ʂ��i�[�B
	m_lStick_y = g_pad.GetLStickYF();

	//���݂̎��Ԃ̎擾�B
	m_nowTime = timeGetTime();

	//�J�[�\���̈ړ������B
	MoveCursor();
	
	//�I������Ă��郁�j���[�̏�Ԃ����ď�����ύX�B
	switch (m_nowMenu)
	{
		//�Q�[���X�^�[�g�B
	case TitleMenu::enGameStart:
		if (g_pad.IsTrigger(enButtonA))
		{
			g_sceneManager->ChangeScene(2);
		}
		break;
		//�Q�[���I���B
	case TitleMenu::enGameEnd:
		if (g_pad.IsTrigger(enButtonA))
		{
			PostQuitMessage(0);
		}
		break;
	default:
		break;
	}
	//�I������Ă��郁�j���[�����ăJ�[�\���̈ʒu���X�V�B
	m_position = CursorPostion[m_nowMenu];
	this->SetupMatrices();
	//�J�[�\���̈ړ�����SE�̍X�V�B
	m_cursorMoveSE.Update();
}

void TitleCursor::MoveCursor()
{
	//�J�[�\���̉��ւ̈ړ��B
	if (m_lStick_y < 0.0f) {
		//��莞�Ԓ����Ȃ��ƃJ�[�\���͓����Ȃ��B
		if (m_nowTime - m_cursorMoveTime > CURSOR_MOVETIME) {
			m_cursorMoveTime = m_nowTime;

			//�I�����郁�j���[���������B
			m_nowMenu += 1;
			//���������ʂ����j���[�̍Ō�����l���傫���Ȃ��ԏ�̃��j���[�Ɉړ�������B
			if (m_nowMenu > TitleMenu::enGameEnd)
			{
				m_nowMenu = TitleMenu::enGameStart;
			}

			//�ړ������Đ��B
			m_cursorMoveSE.Play(FALSE);
			m_cursorMoveSE.SetVolume(0.25f);
		}
	}

	//�J�[�\���̏�ւ̈ړ��B
	if (m_lStick_y > 0.0f) {
		//��莞�Ԓ����Ȃ��ƃJ�[�\���͓����Ȃ��B
		if (m_nowTime - m_cursorMoveTime > CURSOR_MOVETIME) {
			m_cursorMoveTime = m_nowTime;

			//�I�����郁�j���[����グ��B
			m_nowMenu -= 1;
			//���������ʂ����j���[�̍ŏ������l���������Ȃ��ԉ��̃��j���[�Ɉړ�������B
			if (m_nowMenu < TitleMenu::enGameStart)
			{
				m_nowMenu = TitleMenu::enGameEnd;
			}
			//�ړ������Đ��B
			m_cursorMoveSE.Play(FALSE);
			m_cursorMoveSE.SetVolume(0.25f);
		}
	}

	//���X�e�B�b�N��Y�����������͂���Ă��Ȃ��Ȃ�J�[�\���̈ړ����Ԃ��N���A�B
	if (m_lStick_y == 0.0f)
	{
		m_cursorMoveTime = 0;
	}
}