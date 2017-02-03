#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget()
{
	m_depthSurface = NULL;
	m_texture = NULL;
	m_surface = NULL;
	m_texture = NULL;
}

RenderTarget::~RenderTarget()
{
	Release();
}

void RenderTarget::Create(int w,
	int h,
	int mipLevel,
	D3DFORMAT colorFormat,
	D3DFORMAT depthStencilFormat,
	D3DMULTISAMPLE_TYPE multiSampleType,
	int multiSampleQuality)
{
	//デプスステンシルバッファの作成(テクスチャへのレンダリングに使う深度バッファ)
	HRESULT hr = g_pd3dDevice->CreateDepthStencilSurface(
		w,													//深度バッファぼサイズ
		h,													//深度バッファぼサイズ
		static_cast<D3DFORMAT>(depthStencilFormat),			//深度バッファのフォーマット(16bit)
		static_cast<D3DMULTISAMPLE_TYPE>(multiSampleType),	//高度な補間方法の指定
		multiSampleQuality,									//画像の品質レベルの設定
		TRUE,												//深度バッファの制御方法の指定
		&m_depthSurface,									//深度バッファの格納先を示すポインタのアドレス
		NULL												//常にNULLを指定
		);
	//カラーバッファ(レンダリングターゲットとして使用するテクスチャ)を作成。
	hr = g_pd3dDevice->CreateTexture(
		w,													//テクスチャのサイズ
		h,													//テクスチャのサイズ
		mipLevel,											//テクスチャのレベル
		D3DUSAGE_RENDERTARGET,								//レンダリングターゲットとして利用することの明示
		static_cast<D3DFORMAT>(colorFormat),				//テクスチャフォーマット
		D3DPOOL_DEFAULT,									//テクスチャメモリの確保方法
		&m_texture,											//テクスチャの格納先を示すポインタのアドレス
		NULL												//常にNULLを指定
		);
	//テクスチャからレンダリングターゲットにするサーフェスのインターフェースの取得
	m_texture->GetSurfaceLevel(0, &m_surface);

	m_width = w;
	m_height = h;
}

void RenderTarget::Release()
{
	if (m_texture != nullptr) {
		m_texture->Release();
		m_texture = NULL;
	}
	if (m_depthSurface != nullptr) {
		m_depthSurface->Release();
		m_depthSurface = NULL;
	}
	if (m_surface != NULL) {
		m_surface->Release();
		m_surface = NULL;
	}
}