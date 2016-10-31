#pragma once

const int LIGHT_NUM = 4;	//ライトの数

//ライトのクラス
class Light
{

public:
	Light();
	~Light();

	//ライトを初期化。
	void Initialize();

	//ライトの更新
	void Update();

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
	/*!
	*@brief	平行光源の方向を設定。
	*@param[in]	lightNo		ライトの番号
	*@param[in]	dir			方向。
	*/
	void SetDiffuseLightDirection(int lightNo, const D3DXVECTOR4& dir)
	{
		m_diffuseLightDirection[lightNo] = dir;
	}
	/*!
	*@brief	平行光源の色を設定。
	*@param[in]	lightNo		ライトの番号。
	*@param[in]	color		平行光源の色。
	*/
	void SetDiffuseLightColor(int lightNo, const D3DXVECTOR4& color)
	{
		m_diffuseLightColor[lightNo] = color;
	}
	/*!
	* @brief	環境光を設定。
	*/
	void SetAmbientLight(const D3DXVECTOR4& ambient)
	{
		m_ambientLight = ambient;
	}
	//環境光取得
	D3DXVECTOR4 GetAmbientLight()
	{
		return m_ambientLight;
	}
	//ライトの数取得
	int GetLight_Num()
	{
		return LIGHT_NUM;
	}
private:
	D3DXVECTOR4 			m_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
	D3DXVECTOR4				m_diffuseLightColor[LIGHT_NUM];		//ライトの色。
	D3DXVECTOR4				m_ambientLight;						//環境光
};