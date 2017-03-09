#pragma once
#include "2DImage.h"
#include "SoundSource.h"

#define CURSOR_MOVETIME 200


//タイトルのメニューの種類。
enum TitleMenu {
	enGameStart = 0,//ゲーム開始。
	enGameEnd,		//ゲーム終了。
};

//タイトルシーンのカーソル。
class TitleCursor :
	public C2DImage
{
public:
	TitleCursor();
	~TitleCursor();
	//初期化
	void Initialize();
	//更新。
	void Update();
	//カーソルの移動処理。
	void MoveCursor();
private:
	short			m_nowMenu;			//現在選択されているメニューを格納。
	float			m_lStick_y;			//左スティックのY軸の入力量を格納。
	DWORD			m_nowTime;			//現在の時間を格納。
	DWORD			m_cursorMoveTime;	// カーソル移動後経過時間。
	CSoundSource	m_cursorMoveSE;		//カーソルの移動音。
};