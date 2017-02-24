#pragma once
#include "Animation.h"
class EnemySkeleton;
class EnemyGoblin;
class EnemyBoss;

//エネミー全部の処理をするクラス。
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
	Animation m_animation;
	//手前に付いているconstの役割は値を変えない参照と言うの明示的に教えている。
	//後ろに付いているconstの役割は関数の中身で値を変えないと言うのを明示的に教えている。
	const std::vector<EnemySkeleton*>& GetEnemyList() const
	{
		return m_enemyskeletonList;
	}
	//constだと中身を変えたい時に変えれないので変えたい時用のためにもう一つ用意。
	std::vector<EnemySkeleton*>& GetEnemyList()
	{
		return m_enemyskeletonList;
	}
	/*!
	* @brief	⊿タイムに乗算される値を設定。
	*@param[in]	mul		グローバル⊿タイムに乗算される値。この値に0.5を設定するとエネミーの挙動が0.5倍速になる。
	*/
	void SetFrameDeltaTimeMul(float mul);
private:
	//骨型の敵の可変長配列。
	std::vector< EnemySkeleton*> m_enemyskeletonList;
	//ゴブリン型の可変長配列。
	std::vector< EnemyGoblin*>	m_enemyGoblinList;
	//ボス。
	EnemyBoss* m_enemyBoss;
};