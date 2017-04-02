#pragma once
#include <vector>
//リスポーンクラス。
class Respawn
{
public:
	//コンストラクタ。
	Respawn();

	//デストラクタ。
	~Respawn();

	//初期化。
	void Initialize();

	//更新。
	void Update();
private:
	std::vector<btGhostObject*>		m_ghostObjectList;	//ゴースト。剛体の変わりになるもの。
};

