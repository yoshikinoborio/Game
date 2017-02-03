#pragma once
#include "stdafx.h"

/*!
* @brief	パーティクル生成パラメータ。
*/
//パーティクル生成パラメータ構造体の定義。
struct SParicleEmitParameter {
	//初期化。
	void Init()
	{
		memset(this, 0, sizeof(SParicleEmitParameter));
	}
	const char* texturePath;			//!<テクスチャのファイルパス。
	float w;							//!<パーティクルの幅。
	float h;							//!<パーティクルの高さ。
	float intervalTime;					//!<パーティクルの発生間隔。
	D3DXVECTOR3 initSpeed;				//!<初速度。
	D3DXVECTOR3 position;				//!<初期位置。
	float	life;						//!<パーティクルの生存時間。
};

enum ParicleType {
	Star = 0
};

//星。
static SParicleEmitParameter Star_Paricle = {
	"image\\star.png",				//!<テクスチャのファイルパス。
	0.5f,							//!<パーティクルの幅。
	0.5f,							//!<パーティクルの高さ。
	0.01f,							//!<パーティクルの発生間隔。
	D3DXVECTOR3(0.0f,1.0f,0.0f),	//!<初速度。
	D3DXVECTOR3(0.0f,0.0f,0.0f),	//!<位置。
	1.0f							//!<パーティクルの生存時間。
};

static SParicleEmitParameter* ParticleParamPT_Array[] = {
	&Star_Paricle
};