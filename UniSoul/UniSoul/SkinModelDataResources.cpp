#include "stdafx.h"
#include "SkinModelDataResources.h"

SkinModelDataResources::SkinModelDataResources()
{

}


SkinModelDataResources::~SkinModelDataResources()
{
	Release();
}

SkinModelData* SkinModelDataResources::Load(const char* modelPath,Animation* anim)
{
	SkinModelData* originalSkinModelData;	//オリジナルのスキンモデルデータ。
	SkinModelData* skinModelData;			//スキンモデルデータ。

	//モデル名をハッシュ値に変換する。
	int hash = CUtil::MakeHash(modelPath);
	auto& it = m_SkinModelDataList.find(hash);
	//mapにスキンモデルデータが登録されているかいないかを調べる。
	if (it == m_SkinModelDataList.end()) {
		//新規なのでmapに登録。
		originalSkinModelData = new SkinModelData;
		//mapにhashと共にスキンモデルデータを登録。
		m_SkinModelDataList.insert(std::pair<int, SkinModelData*>(hash, originalSkinModelData));
		//モデルをロード。
		originalSkinModelData->LoadModelData(modelPath, anim);
	}
	else {
		//既存のモデルなので使い回す。
		//mapに登録されているスキンモデルデータを入れる。
		originalSkinModelData = it->second;
		//m_skinModelData->CloneModelData(*m_originalSkinModelData, anim);
	}
	skinModelData = new SkinModelData;
	skinModelData->CloneModelData(*originalSkinModelData, anim);
	//クローンされたスキンモデルデータを返す。
	return skinModelData;
}

//void SkinModelDataResources::GC()
//{
//	//参照カウンタが1になっているCSkinModelDataをガベージコレクト。
//	std::vector<CSkinModelDataMap::iterator>	deleteItList;
//	for (
//		CSkinModelDataMap::iterator it = m_skinModelDataMap.begin();
//		it != m_skinModelDataMap.end();
//		it++
//		) {
//		if (it->second.unique()) {
//			//こいつを参照しているモデルはもういない。
//			deleteItList.push_back(it);
//		}
//	}
//}

void SkinModelDataResources::Release()
{
	//mapに登録されたスキンモデルデータを削除。
	for (auto SkinList : m_SkinModelDataList)
	{
		delete SkinList.second;
	}
}