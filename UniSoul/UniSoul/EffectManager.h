#pragma once
#include "PreCompile.h"
class Effect;

//エフェクトマネージャ。
class EffectManager{
public:
	//コンストラクタ
	EffectManager();
	//デストラクタ
	~EffectManager();
	/*!
	*@brief	エフェクトのロード。
	*@details
	* 読み込み済みのエフェクトの場合はロードは行われず、</br>
	* 既存のエフェクトが返ってくる
	*@param[in]	filePath	ロードするエフェクトのファイルパス。
	*@return	ロードしたエフェクトファイル。
	*/
	ID3DXEffect* LoadEffect(const char* filePath);
	//解放
	void Release();
private:
	//mapはユニークな要素を格納する連想コンテナの一種であり、キーとそれに対応する値を格納(互いに等しい二つのキーを持つ要素がmapに格納されることは無い)
	std::map<int, ID3DXEffect*>		m_effectDictinary;	//CEffectのインスタンスのディクショナリ。ファイルパスのハッシュ値をキーに持ち、CEffectのインスタンスを値に持つ。
};
