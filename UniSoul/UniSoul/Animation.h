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
	void SetAnimationEndtime(int animationSetIndex, double endTime){
		if (animationSetIndex < m_numAnimSet) {
			m_animationEndTime[animationSetIndex] = endTime;
		}
	}

	//アニメーションのループの設定。
	//FALSEならアニメーションをループさせない。
	void SetAnimationLoopFlag(int animationSetIndex, bool loopFlag)
	{
		if (animationSetIndex < m_numAnimSet) {
			m_animationLoopFlags[animationSetIndex] = loopFlag;
		}
	}

	//アニメーションの再生中判定。
	bool IsPlay() const
	{
		return !m_isAnimEnd;
	}

	//ローカルアニメーションタイムの取得。
	double GetlocalAnimationTime()
	{
		return m_localAnimationTime;
	}

	//補間時間を元にトラックの重みを更新。
	void UpdateTrackWeights();
#if 0
	// アニメーションのブレンディング再生
	// 引き数: int型 再生したいアニメーションのインデックス
	void BlendAnimation(int animationSetIndex);
#endif
	int GetNumAnimationSet() const{
		return m_numAnimSet;
	}

	void Update(float deltaTime);
private:
	ID3DXAnimationController*				m_pAnimController;		//アニメーションコントローラ。
	int										m_numAnimSet;			//アニメーションセットの数。
	std::unique_ptr<ID3DXAnimationSet*[]>	m_animationSets;		//アニメーションセットの配列。
	std::unique_ptr<bool[]>					m_animationLoopFlags;	//アニメーションのループフラグ。	
	//スマートポインター(ポインタで渡されたクラスのデストラクタを有効範囲からると呼び出す)
	std::unique_ptr<float[]>				m_blendRateTable;		//ブレンディングレートのテーブル。
	std::unique_ptr<double[]>				m_animationEndTime;		//アニメーションの終了タイム。デフォルトは-1.0が入っていて、-1.0が入っている場合はID3DXAnimationSetのアニメーション終了タイムが優先される。
	int										m_oldAnimationSetNo;	// 1フレーム前のアニメーションセットの番号
	double									m_localAnimationTime;	//ローカルアニメーションタイム。
	int										m_currentAnimationSetNo;//現在再生中のアニメーショントラックの番号。
	int										m_currentTrackNo;		//現在のトラックの番号。
	int										m_numMaxTracks;			//アニメーショントラックの最大数。
	bool									m_isBlending;			//アニメーションブレンディング中かどうかのフラグ。
	bool									m_isAnimEnd;			//アニメーションの終了フラグ。
	bool									m_isInterpolate;		//補間中かのフラグ
	float									m_interpolateEndTime;	//補間終了時間。
	float									m_interpolateTime;		//補間時間。
};