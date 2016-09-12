#pragma once
#include "PreCompile.h"
//アニメーションクラス
class Animation
{
public:
	Animation() 
	{
		m_pAnimController = nullptr;
		m_numAnimSet = 0;
		m_isBlending = false;
		m_isInterpolate = false;
		m_numMaxTracks = 0;
		m_interpolateTime = 0.0f;
		m_interpolateEndTime = 0.0f;
	};
	~Animation();
	void Initialize(ID3DXAnimationController* anim);
	void Update(float deltaTime);

	// アニメーション再生関数
	// 引き数: int型 再生したいアニメーションのインデックス
	void PlayAnimation(int animationSetIndex);

	// アニメーション再生関数
	// 引き数: int型 再生したいアニメーションのインデックス
	//		　 float型 補完時間
	void PlayAnimation(int animationSetIndex, float interpolateTime);

	// アニメーション再生速度を設定
	void SetAnimSpeed(float speed);

	//アニメーションの終了タイムを設定する関数
	//引き数:int型 アニメーションインデックス
	//      :double型 アニメーションの終了タイム
	//※-1.0を指定するとデフォルトの終了時間が設定されます
	void SetAnimationEndtime(int animationIndex, double endTime){
		m_animationEndTime[animationIndex] = endTime;
	}
#if 0
	// アニメーションのブレンディング再生
	// 引き数: int型 再生したいアニメーションのインデックス
	void BlendAnimation(int animationSetIndex);
#endif
	int GetNumAnimationSet() const{
		return m_numAnimSet;
	}
private:
	ID3DXAnimationController*				m_pAnimController;		//アニメーションコントローラ。
	int										m_numAnimSet;			//アニメーションセットの数。
	std::unique_ptr<ID3DXAnimationSet*[]>	m_animationSets;		//アニメーションセットの配列。
	//スマートポインター(ポインタで渡されたクラスのデストラクタを有効範囲からると呼び出す)
	std::unique_ptr<float[]>				m_blendRateTable;		//ブレンディングレートのテーブル。
	std::unique_ptr<double[]>				m_animationEndTime;		//アニメーションの終了タイム。デフォルトは-1.0が入っていて、-1.0が入っている場合はID3DXAnimationSetのアニメーション終了タイムが優先される。
	int										m_oldAnimationSetNo;	// 1フレーム前のアニメーションセットの番号
	double									m_localAnimationTime;	//ローカルアニメーションタイム。
	int										m_currentAnimationSetNo;//現在再生中のアニメーショントラックの番号。
	int										m_currentTrackNo;		//現在のトラックの番号。
	int										m_numMaxTracks;			//アニメーショントラックの最大数。
	bool									m_isBlending;			//アニメーションブレンディング中かどうかのフラグ
	bool									m_isInterpolate;		//補間中かのフラグ
	float									m_interpolateEndTime;	//補間終了時間。
	float									m_interpolateTime;		//補間時間。
};