#pragma once
#include "SkinModelData.h"
#include <map>
class SkinModel;
class Animation;

//モデルを読み込んで使いまわすかどうかを決めるクラス。
class SkinModelDataResources
{
public:
	//コンストラクタ。
	SkinModelDataResources();

	//デストラクタ。
	~SkinModelDataResources();

	//モデルのロード。
	//モデルのファイルパス。
	//アニメーション。
	SkinModelData* Load(
		const char* modelPath,
		Animation* anim
	);
	
	//SkinModelDataのリリースを破棄。
	void Release();
	///*!
	//* @brief	ガベージコレクトの実行。
	//*@details
	//* 参照カウンタがになっているCSkinModelDataが解放されます。
	//*/
	//void GC();
private:
	std::map<int, SkinModelData*> m_SkinModelDataList;	//スキンモデルデータのリスト。
};