#pragma once

//視野角作成クラス。
class CreateViewAngle
{
public:
	//コンストラクタ。
	CreateViewAngle();

	//デストラクタ。
	~CreateViewAngle();

	//視野角作成。
	//第一引数はプレイヤーに向かうベクトル。
	//第二引数は自分の向きベクトル。
	//戻り値は作成した視野角。
	float CreateView(const D3DXVECTOR3& TargetDir, const D3DXMATRIX& MyDir);
};

