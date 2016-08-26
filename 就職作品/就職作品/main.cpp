#include "stdafx.h"
#include "Game.h"

Game* game;

//-----------------------------------------------------------------------------
// Name: 初期化。
//-----------------------------------------------------------------------------
void Init()
{
	game = new Game;
	game->Initialize();
}

//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
void Render()
{
	game->Draw();
}

/*!-----------------------------------------------------------------------------
*@brief	更新処理。
-----------------------------------------------------------------------------*/
void Update()
{
	game->Update();
}

//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	game->Terminate();
}
