#pragma once
#include "SceneBase.h"
#include "Title.h"
#include "TitleCursor.h"

//タイトルシーン
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	//初期化。
	void Initialize();
	//更新。
	void Update();
	//描画。
	void Draw();
	//解放。
	void Terminate();
private:
	//タイトルの画像。
	Title m_title;
	//タイトルに表示されているカーソル。
	TitleCursor m_titleCursor;
};

//どこでも使えるようにextern
extern TitleScene* titleScene;