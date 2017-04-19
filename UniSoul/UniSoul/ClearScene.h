#pragma once
#include "SceneBase.h"
#include "Clear.h"
#include "SoundSource.h"

//クリアシーン。
class ClearScene : public SceneBase
{
public:
	//コンストラクタ。
	ClearScene();

	//デストラクタ。
	~ClearScene();

	//初期化。
	void Initialize();

	//更新。
	void Update();

	//描画。
	void Draw();
private:
	Clear			m_clear;			//ゲームクリア画面の画像。
	CSoundSource	m_clearSceneBgm;	//クリアシーンでのBGM。
	float			m_bgmVolume = 0.0f;	//BGMのボリューム。
};

//どこでも使えるようにextern
extern ClearScene* clearScene;