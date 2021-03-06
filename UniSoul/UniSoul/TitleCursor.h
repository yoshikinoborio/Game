#pragma once
#include "2DImage.h"
#include "SoundSource.h"

//カーソルが次の移動ができるまで待機する時間。
namespace {
	const short CURSOR_MOVEWAITTIME = 200;
}

//タイトルシーンのカーソル。
class TitleCursor :
	public C2DImage
{
public:
	//タイトルのメニューの種類。
	enum class TitleMenu {
		enGameStart = 0,//ゲーム開始。
		enGameEnd,		//ゲーム終了。
	};

	//コンストラクタ。
	TitleCursor();

	//デストラクタ。
	~TitleCursor();

	//初期化
	void Initialize();

	//更新。
	void Update();

	//カーソルの移動処理。
	void MoveCursor();

	//カーソルの移動音の再生。
	void MoveCursorSE();

	//ボタンを押された時の決定音の再生。
	void DecideSE();

	//各メニューの処理。
	void MenuProcess();
private:
	int				m_nowMenu;			//現在選択されているメニューを格納。
	float			m_lStick_y;			//左スティックのY軸の入力量を格納。
	DWORD			m_nowTime;			//現在の時間を格納。
	DWORD			m_cursorMoveTime;	//カーソル移動後経過時間。
	CSoundSource	m_cursorMoveSE;		//カーソルの移動音。
	CSoundSource	m_cursorDecideSE;	//ボタンを押された時の決定音。
	bool			m_gameStratFlag;	//スタートで決定ボタンを押すとTRUEになる。
	bool			m_gameEndFlag;		//ゲーム終了で決定ボタンを押すとTRUEになる。
};