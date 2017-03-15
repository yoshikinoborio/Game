#pragma once

namespace {
	const int LIGHT_NUM = 4;	//ライトの数
}

//ライトのクラス
class Light
{

public:
	//コンストラクタ。
	Light();

	//デストラクタ。
	~Light();

	//ライトを初期化。
	void Initialize();

	//ライトの方向取得
	D3DXVECTOR4* GetDiffuseLightDirection()
	{
		return m_diffuseLightDirection;
	}

	//ライトの色取得
	D3DXVECTOR4* GetDiffuseLightColor()
	{
		return m_diffuseLightColor;
	}

	//平行光源の方向を設定。
	//ライトの番号
	//方向。
	void SetDiffuseLightDirection(const int& lightNo, const D3DXVECTOR4& dir)
	{
		m_diffuseLightDirection[lightNo] = dir;
	}

	//平行光源の色を設定。
	//ライトの番号。
	//平行光源の色。
	void SetDiffuseLightColor(const int& lightNo, const D3DXVECTOR4& color)
	{
		m_diffuseLightColor[lightNo] = color;
	}

	//環境光を設定。
	void SetAmbientLight(const D3DXVECTOR4& ambient)
	{
		m_ambientLight = ambient;
	}

	//環境光取得
	const D3DXVECTOR4& GetAmbientLight() const
	{
		return m_ambientLight;
	}

	//ライトの数取得
	const int& GetLight_Num() const
	{
		return LIGHT_NUM;
	}
private:
	D3DXVECTOR4 			m_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
	D3DXVECTOR4				m_diffuseLightColor[LIGHT_NUM];		//ライトの色。
	D3DXVECTOR4				m_ambientLight;						//環境光
};