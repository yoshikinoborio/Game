#pragma once
#include "SkinModel.h"

//アニメーションする3Dモデルの基底クラス。
class AnimationModel3D
{
public:
	AnimationModel3D();
	~AnimationModel3D();
	//純粋仮想関数はある基底クラス内のメソッドを派生クラス内で必ず実装(定義)してもらいたい場合、純粋仮想関数で宣言する。
	//純粋仮想関数で宣言されたクラスを継承する場合、必ずオーバーライドしなければならない。
	//基底クラスのメンバメソッドを継承クラスで変更する事ができる。簡単に言えば、再定義するという事。
	//この基底クラスの関数(オーバーライドされる関数)を仮想関数と言う。
	virtual void Initialize() = 0;
	virtual void Update() = 0;
protected:
	SkinModelData	m_skinModelData;	//スキンモデルデータ。
	SkinModel		m_skinModel;		//スキンモデル。
	Animation		m_animation;		//アニメーション。
};