#pragma once

//キャラクターの回転。
class Turn
{
public:
	//コンストラクタ。
	Turn();

	//デストラクタ。
	~Turn();

	//回転処理の初期化。
	void Turn::Initialize();

	//回転処理の更新。
	float Turn::Update(bool isTurn, float currentAngleY);

	//現在の方向の取得。
	const float& GetCurrentAngleY() const
	{
		return m_currentAngleY;

	}

private:
	float	m_currentAngleY;	//現在の方向。
	float	m_targetAngleY;		//向きたい方向。
	float	m_turnSpeed;		//回転速度。
	bool	m_isTurn;			//回転フラグ。
};