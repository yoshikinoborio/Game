#include "stdafx.h"
#include "CreateViewAngle.h"

//コンストラクタ。
CreateViewAngle::CreateViewAngle()
{
}

//デストラクタ。
CreateViewAngle::~CreateViewAngle()
{

}

float CreateViewAngle::CreateView(const D3DXVECTOR3& TargetDir, const D3DXMATRIX& MyDir)
{
	//自分の向きベクトル。
	D3DXVECTOR3 Dir = D3DXVECTOR3(MyDir.m[3][0],MyDir.m[3][1],MyDir.m[3][2]);

	//プレイヤーへの向きベクトル。
	D3DXVECTOR3 PlayerDir = TargetDir;

	//二つのベクトルを正規化。
	D3DXVec3Normalize(&Dir, &Dir);
	D3DXVec3Normalize(&PlayerDir, &PlayerDir);

	//正規化した二つのベクトルの内積を計算。
	float dot = D3DXVec3Dot(&Dir, &PlayerDir);
	//内積の値の逆余弦からラジアンを求める。
	float rad = acos(dot);
	//ラジアンから角度に変換し実際の角度差を求める。
	float selfangle D3DXToDegree(rad);

	//作成した視野角を返す。
	return selfangle;
}
