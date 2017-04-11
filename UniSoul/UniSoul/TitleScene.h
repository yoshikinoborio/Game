#pragma once
#include "SceneBase.h"
#include "Title.h"
#include "TitleCursor.h"
#include "SoundSource.h"

//タイトルシーン
class TitleScene : public SceneBase
{
public:
	//コンストラクタ。
	TitleScene();

	//デストラクタ。
	~TitleScene();

	//初期化。
	void Initialize();

	//更新。
	void Update();
	
	//描画。
	void Draw();
private:
	Title			m_title;		//タイトルの画像。
	TitleCursor		m_titleCursor;	//タイトルに表示されているカーソル。
	CSoundSource	m_soundTitleBgm;//タイトル画面のBGM。
};

//どこでも使えるようにextern
extern TitleScene* titleScene;