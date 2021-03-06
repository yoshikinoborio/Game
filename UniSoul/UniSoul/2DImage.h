#pragma once

class C2DImage
{
public:
	//コンストラクタ。
	C2DImage();

	//デストラクタ。
	~C2DImage();

	//初期化。
	void Initialize();

	//描画。
	void Render();

	//行列作成。
	void SetupMatrices();

	//画像を拡大して移動させるのではなくて移動してから拡大する事によって
	//画像の原点がスプライトの端に来る。
	void SetupSlideMatrices();

	//スケールの設定。
	void SetScale(D3DXVECTOR2& scale)
	{
		m_scale = scale;
	}

	//位置の設定。
	void SetPosition(D3DXVECTOR2& position)
	{
		m_position = position;
	}

	//スプライト生成関数
	HRESULT CreateSprite();	
protected:
	D3DXVECTOR2				m_position;			//位置情報
	float					m_angle;			//回転情報
	D3DXVECTOR2				m_scale;			//スケール情報
	LPDIRECT3DTEXTURE9		m_pTexture;			//テクスチャ
	D3DCOLOR				m_backColor;		//背景カラー
	LPCTSTR					m_texFileName;		//テクスチャファイル名
	D3DXVECTOR2				m_texCenter;		//テクスチャの中点
	RECT					m_rect;				//描画矩形
	D3DXMATRIX				m_transformMatrix;	//変換行列
	LPD3DXSPRITE			m_pSprite;			//スプライト
};

