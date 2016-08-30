#pragma once
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Light.h"
#include "Pad.h"

class Game
{
public:
	//コンストラクタ
	Game();
	//デストラクタ
	~Game();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();
	//解放
	void Terminate();
	//プレイヤーのインスタンスの取得
	Player* GetPlayer()
	{
		return &player;
	}
	//ライトのインスタンスの取得
	Light* GetLight()
	{
		return &light;
	}
	//カメラのインスタンスの取得
	Camera* GetCamera()
	{
		return &camera;
	}
	//ステージのインスタンスの取得
	Stage* GatStage()
	{
		return &stage;
	}
private:
	Player player;
	Camera camera;
	Stage stage;
	Light light;
};

extern Game* game;
extern Pad g_pad;				//どこでも使えるようにextern