//テクスチャの読み込み・画像表示
#include "stdafx.h"
#include "2DImage.h"

C2DImage::C2DImage()
{
}


C2DImage::~C2DImage()
{
}

void C2DImage::Initialize()
{

	CreateSprite();
	D3DXIMAGE_INFO imgInfo;										//画像情報格納用構造体
	D3DXCreateTextureFromFileEx(g_pd3dDevice, this->m_texFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &imgInfo, NULL, &this->m_pTexture);	//テクスチャ読込
	this->m_texCenter = D3DXVECTOR2((float)imgInfo.Width / 2, (float)imgInfo.Height / 2);	//テクスチャの中点セット
	RECT rec = { 0, 0, imgInfo.Width, imgInfo.Height };			//描画領域
	memcpy(&this->m_rect, &rec, sizeof(RECT));					//描画領域セット
}

void C2DImage::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);		//スプライト描画開始
	m_pSprite->SetTransform(&this->m_transformMatrix);	//変換行列セット
	m_pSprite->Draw(this->m_pTexture, &this->m_rect, &D3DXVECTOR3(this->m_texCenter.x, this->m_texCenter.y, 0.0f), NULL, this->m_backColor);	//スプライトにテクスチャ貼付け
	m_pSprite->End();	//スプライト描画終了
}

void C2DImage::SetupMatrices()
{
	D3DXMatrixIdentity(&this->m_transformMatrix);	//ワールド行列初期化
	D3DXMatrixTransformation2D(&this->m_transformMatrix, NULL, 0.0f, &this->m_scale, NULL, D3DXToRadian(this->m_angle), &this->m_position);	//変換行列作成
}

HRESULT C2DImage::CreateSprite()
{
	//特定のデバイスと関連付けられているスプライトオブジェクトを作成する。
	if (FAILED(D3DXCreateSprite(
		g_pd3dDevice,	//インターフェイスへのポインタ。スプライトに関連付けられるデバイス。
		&m_pSprite		//インターフェイスへのポインタのアドレス。このインターフェイスを使ってスプライト関数にアクセスする。
	)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}

void C2DImage::SetupMatrices2()
{
	D3DXMatrixIdentity(&this->m_transformMatrix);	//ワールド行列初期化

	//画像の半分ずらしている。
	D3DXMatrixTranslation(&this->m_transformMatrix, this->m_texCenter.x, 0.0f, 0.0f);
	//D3DXMatrixTransformation2D(&this->m_transformMatrix, NULL, 0.0f, &this->m_scale, NULL, D3DXToRadian(this->m_angle), this->m_position);	//変換行列作成
	//ずらした値から変換行列の作成。
	{
		D3DXMATRIX scale;
		D3DXMATRIX rotation;
		D3DXMATRIX position;
		D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, 1.0f);
		D3DXMatrixRotationYawPitchRoll(&rotation, 0.0f, 0.0f, m_angle);
		D3DXMatrixTranslation(&position, m_position.x, m_position.y, 0.0f);
		m_transformMatrix = m_transformMatrix*scale*rotation*position;
	}
	//ずらした分を戻す。
	m_transformMatrix._41 -= this->m_texCenter.x;
}
