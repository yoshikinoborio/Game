#pragma once
//レンダリングターゲット。
class RenderTarget {
public:
	//コンストラクタ
	RenderTarget();

	//デストラクタ
	~RenderTarget();

	//解放
	void Release();
	/*!
	*@brief	レンダリングターゲットの作成。
	*@param[in]	w					レンダリングターゲットの幅。
	*@param[in]	h					レンダリングターゲットの高さ。
	*@param[in]	mipLevel			ミップマップレベル。
	*@param[in]	colorFormat			カラーバッファのフォーマット。
	*@param[in]	depthStencilFormat	デプスステンシルバッファのフォーマット。
	*@param[in]	multiSampleType		マルチサンプリングの種類。
	*@param[in]	multiSampleQuality	マルチサンプリングの品質。
	*/
	void Create(
		const int& w,
		const int& h,
		const int& mipLevel,
		const D3DFORMAT& colorFormat,
		const D3DFORMAT& depthStencilFormat,
		const D3DMULTISAMPLE_TYPE& multiSampleType,
		const int& multiSampleQuality);

	//サーフェスの取得
	const LPDIRECT3DSURFACE9& GetSurface() const
	{
		return m_surface;
	}

	//デプスステンシルバッファの取得
	const LPDIRECT3DSURFACE9& GetDepthStencilBuffer() const
	{
		return m_depthSurface;
	}

	//テクスチャの取得
	const LPDIRECT3DTEXTURE9& GetTexture() const
	{
		return m_texture;
	}

	//幅を取得。
	const int& GetWidth() const
	{
		return m_width;
	}

	//高さを取得
	const int& GetHeight() const
	{
		return m_height;
	}

private:
	LPDIRECT3DSURFACE9		m_depthSurface;		//深度バッファ用のサーフェイス(デプスステンシルバッファ)
	LPDIRECT3DTEXTURE9		m_texture;			//書き込み先のテクスチャ。
	LPDIRECT3DSURFACE9		m_surface;			//サーフェイス
	int						m_width = 0;		//幅
	int						m_height = 0;		//高さ
};