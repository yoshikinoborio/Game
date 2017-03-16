#pragma once
#include "Animation.h"
class EnemySkeleton;
class EnemyGoblin;
class EnemyBoss;

//エネミー全部の処理をするクラス。
class EnemyManager
{
public:
	//コンストラクタ。
	EnemyManager();

	//デストラクタ。
	~EnemyManager();

	//初期化。
	void Initialize();

	//更新。
	void Update();

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
	
	
	const std::vector<EnemySkeleton*>& GetEnemyList() const
	{
		return m_enemyskeletonList;
	}

	//constだと中身を変えたい時に変えれないので変えたい時用のためにもう一つ用意。
	std::vector<EnemySkeleton*>& GetEnemyList()
	{
		return m_enemyskeletonList;
	}

	EnemyBoss& GetBoss() 
	{
		return *m_enemyBoss;
	}

	//⊿タイムに乗算される値を設定。
	//グローバル⊿タイムに乗算される値。この値に0.5を設定するとエネミーの挙動が0.5倍速になる。
	void SetFrameDeltaTimeMul(float mul);
private:
	std::vector< EnemySkeleton*>	m_enemyskeletonList;	//骨型の敵の可変長配列。
	std::vector< EnemyGoblin*>		m_enemyGoblinList;		//ゴブリン型の可変長配列。
	EnemyBoss*						m_enemyBoss;			//ボス。
};