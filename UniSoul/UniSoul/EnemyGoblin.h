#pragma once
#include "EnemyBase.h"

class UnityChan;

//ゴブリンのクラス。
class EnemyGoblin : public EnemyBase
{
public:

	//コンストラクタ。
	EnemyGoblin();

	//デストラクタ。
	~EnemyGoblin();

	//初期化。
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale)override;

	//更新。
	void Update()override;

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver)override;

	//ダメージ。
	void Damage();
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//コリジョンオブジェクト。
	UnityChan*							m_unitytyan;			//プレイヤーのインスタンス。
	D3DXVECTOR3							m_posDifference;		//プレイヤーとの距離。
	float								m_atrTime;				//この時間以上になったら当たりを発生させる。
};