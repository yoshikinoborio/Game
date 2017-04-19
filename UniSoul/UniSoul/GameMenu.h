#pragma once

//ゲームシーンのメニュー画面の処理。
class GameMenu
{
public:

	//コンストラクタ。
	GameMenu();

	//デストラクタ。
	~GameMenu();

	//初期化。
	void Initialize();

	//更新。
	void Update();

	//描画。
	void Draw();
private:
	D3DVIEWPORT9 m_viewPort;	//ビューポート。
};