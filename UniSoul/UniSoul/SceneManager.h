#pragma once
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"

//シーンの管理クラス。
class SceneManager
{
public:
	
	//コンストラクタ。
	SceneManager();

	//デストラクタ。
	~SceneManager();

	//初期化。
	void Initialize();

	//更新。
	void Update();

	//描画。
	void Draw();

	//シーンの切り替え。
	void ChangeScene(const int& key);

	//解放。
	void Terminate();
private:
	SceneBase* m_scenes;
	bool m_clearFlag;		//trueはクリア、falseはゲームオーバー。
	int m_nextScene;		//切り替えるシーン番号。
};

extern SceneManager* g_sceneManager;
extern SceneBase* g_pScenes;
