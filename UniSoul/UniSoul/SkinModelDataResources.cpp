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
	SkinModelData* originalSkinModelData;	//�I���W�i���̃X�L�����f���f�[�^�B
	SkinModelData* skinModelData;			//�X�L�����f���f�[�^�B

	//���f�������n�b�V���l�ɕϊ�����B
	int hash = CUtil::MakeHash(modelPath);
	auto& it = m_SkinModelDataList.find(hash);
	//map�ɃX�L�����f���f�[�^���o�^����Ă��邩���Ȃ����𒲂ׂ�B
	if (it == m_SkinModelDataList.end()) {
		//�V�K�Ȃ̂�map�ɓo�^�B
		originalSkinModelData = new SkinModelData;
		//map��hash�Ƌ��ɃX�L�����f���f�[�^��o�^�B
		m_SkinModelDataList.insert(std::pair<int, SkinModelData*>(hash, originalSkinModelData));
		//���f�������[�h�B
		originalSkinModelData->LoadModelData(modelPath, anim);
	}
	else {
		//�����̃��f���Ȃ̂Ŏg���񂷁B
		//map�ɓo�^����Ă���X�L�����f���f�[�^������B
		originalSkinModelData = it->second;
		//m_skinModelData->CloneModelData(*m_originalSkinModelData, anim);
	}
	skinModelData = new SkinModelData;
	skinModelData->CloneModelData(*originalSkinModelData, anim);
	//�N���[�����ꂽ�X�L�����f���f�[�^��Ԃ��B
	return skinModelData;
}

//void SkinModelDataResources::GC()
//{
//	//�Q�ƃJ�E���^��1�ɂȂ��Ă���CSkinModelData���K�x�[�W�R���N�g�B
//	std::vector<CSkinModelDataMap::iterator>	deleteItList;
//	for (
//		CSkinModelDataMap::iterator it = m_skinModelDataMap.begin();
//		it != m_skinModelDataMap.end();
//		it++
//		) {
//		if (it->second.unique()) {
//			//�������Q�Ƃ��Ă��郂�f���͂������Ȃ��B
//			deleteItList.push_back(it);
//		}
//	}
//}

void SkinModelDataResources::Release()
{
	//map�ɓo�^���ꂽ�X�L�����f���f�[�^���폜�B
	for (auto SkinList : m_SkinModelDataList)
	{
		delete SkinList.second;
	}
}