#pragma once
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"

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
	void ChangeScene(int key);

	//解放。
	void Terminate();
private:
	SceneBase* m_scenes;
	bool m_clearFlag;		//trueはクリア、falseはゲームオーバー。
	int m_nextScene;
};

extern SceneManager* g_sceneManager;
extern SceneBase* g_pScenes;
