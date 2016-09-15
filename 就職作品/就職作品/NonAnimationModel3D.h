#pragma once
#include "Model3D.h"

//アニメーションしない3Dモデルの基底クラス
class NonAnimationModel3D
{
public:
	NonAnimationModel3D();
	~NonAnimationModel3D();
	//純粋仮想関数
	virtual void Initialize() = 0;
	//純粋仮想関数
	virtual void Update() = 0;
protected:
	Model3D	m_model3d;	//アニメーションしない3D関係を表示するModel3Dのインスタンスを保持
};