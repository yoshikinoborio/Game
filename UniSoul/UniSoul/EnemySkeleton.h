#pragma once
#include "EnemyBase.h"

class UnityChan;

static D3DXVECTOR3 EnemyCource[] = {
#include "EnemyCource.h"
};

//スケルトンクラス。
class EnemySkeleton : public EnemyBase
{
public:
	//コンストラクタ。
	EnemySkeleton();

	//デストラクタ。
	~EnemySkeleton();

	//初期化。
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale)override;

	//更新。
	void Update()override;

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver)override;

	//スケルトンが発見状態の時の回転と移動の処理。
	void FindMove();

	//スケルトンが索敵中の時の回転と移動の処理。
	void SearchMove();

	//ダメージを受ける処理。
	void Damage();

	void SetFlag(bool flg)
	{
		m_lightFlag = flg;
	}
private:
	UnityChan*			m_unitytyan;				//プレイヤーのインスタンス。
	D3DXVECTOR3			m_unityPos;					//プレイヤーの位置。
	D3DXVECTOR3			m_posDifference;			//プレイヤーとの距離。
	D3DXVECTOR3			m_SkeDir;					//敵の向きベクトル。
	float				m_walkTimer;				//歩く時間。
	float				m_atrTime;					//この時間以上になったら当たりを発生させる。
	int					m_courceArray;				//コース定義の数。
	int					m_mostNearCourceIndex;		//一番近いコース定義。
	bool				m_lightFlag;				
};