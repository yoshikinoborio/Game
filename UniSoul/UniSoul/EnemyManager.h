#pragma once
#include "Animation.h"
class EnemyBase;
class EnemySkeleton;
class EnemyGoblin;
class EnemyBoss;

//エネミー全部の処理をするクラス。
class EnemyManager
{
public:
	//エネミーのタイプ。
	enum  class EnemyType
	{
		Skeleton = 0,	//骨型。
		Goblin,			//ゴブリン。
		Boss			//ボス。
	};
	//コンストラクタ。
	EnemyManager();

	//デストラクタ。
	~EnemyManager();

	//初期化。
	void Initialize();

	//更新。
	void Update();

	//エネミーリストの更新。
	void EnemyListUpdate();

	//ボスの更新。
	void EnemyBossUpdate();

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowCaster);

	//敵を生成する処理。
	void EnemyCreate();
	
	const std::vector<EnemyBase*>& GetEnemyList() const
	{
		return m_enemyList;
	}

	//constだと中身を変えたい時に変えれないので変えたい時用のためにもう一つ用意。
	std::vector<EnemyBase*>& GetEnemyList()
	{
		return m_enemyList;
	}

	//ボスのインスタンス取得。
	EnemyBoss& GetBoss() 
	{
		return *m_enemyBoss;
	}

	//敵を生成する位置とフラグの設定。
	void SetEnemyCreate(const D3DXVECTOR3& pos,bool flg)
	{
		m_createPos = pos;
		m_createEnemyFlag = flg;
	}
	//�刄^イムに乗算される値を設定。
	//グローバル�刄^イムに乗算される値。この値に0.5を設定するとエネミーの挙動が0.5倍速になる。
	void SetFrameDeltaTimeMul(float mul);
private:
	std::vector< EnemyBase*>		m_enemyList;			//ボス以外を除く敵の可変長配列。
	EnemyBoss*						m_enemyBoss;			//ボス。
	bool							m_createEnemyFlag;		//敵を生成するフラグ。
	D3DXVECTOR3						m_createPos;			//敵を生成する時に使う位置情報を格納。
};