#include "stdafx.h"
#include "TitleCursor.h"
#include "SceneManager.h"

//各メニューの位置情報。
//左からスタート、終了。
const D3DXVECTOR2  CursorPostion[2] = { { 820.0f, 265.0f },{820.0f, 320.0f} };


TitleCursor::TitleCursor()
{
	//カーソルをゲームスタートの位置から開始。
	m_nowMenu = TitleMenu::enGameStart;
	//各変数の初期化。
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
	//カーソルの移動時のSEの初期化。
	m_cursorMoveSE.Init("image/UniSoul_CursorMoveSE.wav");
}

void TitleCursor::Update()
{
	//左スティックY軸の入力量を格納。
	m_lStick_y = g_pad.GetLStickYF();

	//現在の時間の取得。
	m_nowTime = timeGetTime();

	//カーソルの移動処理。
	MoveCursor();
	
	//選択されているメニューの状態を見て処理を変更。
	switch (m_nowMenu)
	{
		//ゲームスタート。
	case TitleMenu::enGameStart:
		if (g_pad.IsTrigger(enButtonA))
		{
			g_sceneManager->ChangeScene(2);
		}
		break;
		//ゲーム終了。
	case TitleMenu::enGameEnd:
		if (g_pad.IsTrigger(enButtonA))
		{
			PostQuitMessage(0);
		}
		break;
	default:
		break;
	}
	//選択されているメニューを見てカーソルの位置を更新。
	m_position = CursorPostion[m_nowMenu];
	this->SetupMatrices();
	//カーソルの移動時のSEの更新。
	m_cursorMoveSE.Update();
}

void TitleCursor::MoveCursor()
{
	//カーソルの下への移動。
	if (m_lStick_y < 0.0f) {
		//一定時間超えないとカーソルは動かない。
		if (m_nowTime - m_cursorMoveTime > CURSOR_MOVETIME) {
			m_cursorMoveTime = m_nowTime;

			//選択するメニューを一つ下げる。
			m_nowMenu += 1;
			//下げた結果がメニューの最後よりも値が大きいなら一番上のメニューに移動させる。
			if (m_nowMenu > TitleMenu::enGameEnd)
			{
				m_nowMenu = TitleMenu::enGameStart;
			}

			//移動音を再生。
			m_cursorMoveSE.Play(FALSE);
			m_cursorMoveSE.SetVolume(0.25f);
		}
	}

	//カーソルの上への移動。
	if (m_lStick_y > 0.0f) {
		//一定時間超えないとカーソルは動かない。
		if (m_nowTime - m_cursorMoveTime > CURSOR_MOVETIME) {
			m_cursorMoveTime = m_nowTime;

			//選択するメニューを一つ上げる。
			m_nowMenu -= 1;
			//下げた結果がメニューの最初よりも値が小さいなら一番下のメニューに移動させる。
			if (m_nowMenu < TitleMenu::enGameStart)
			{
				m_nowMenu = TitleMenu::enGameEnd;
			}
			//移動音を再生。
			m_cursorMoveSE.Play(FALSE);
			m_cursorMoveSE.SetVolume(0.25f);
		}
	}

	//左スティックのY軸が何も入力されていないならカーソルの移動時間をクリア。
	if (m_lStick_y == 0.0f)
	{
		m_cursorMoveTime = 0;
	}
}