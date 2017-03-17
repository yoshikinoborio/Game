#pragma once
#include "RenderTarget.h"

namespace {
	static const int	MGF_DOWN_SAMPLE_COUNT = 4;							//MGFダウンサンプリングの回数。
	static const int	NUM_WEIGHTS = 8;									//ガウスブラーの重み。
}

class Bloom {
public:
	/*!
	* @brief	コンストラクタ。
	*/
	Bloom();
	/*!
	* @brief	デストラクタ。
	*/
	~Bloom();
	/*!
	* @brief	描画。
	*/
	void Render();
	//重みの更新。
	void UpdateWeight(float dispersion);
private:
	
	LPD3DXEFFECT		m_effect;												//シェーダーエフェクト。
	RenderTarget		m_luminanceRenderTarget;								//輝度を抽出するためのレンダリングターゲット。
	RenderTarget		m_downSamplingRenderTarget[MGF_DOWN_SAMPLE_COUNT][2];	//MGFダウンサンプリング用のレンダリングターゲット。
	float				m_weights[NUM_WEIGHTS];								//ガウスブラーで使う重みテーブル。
};