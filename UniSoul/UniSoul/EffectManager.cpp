#include "stdafx.h"
#include "EffectManager.h"

namespace{
	
	//�����񂩂�32bit�̃n�b�V���l���쐬�B
	//�n�b�V���l����闝�R�͕�����ŒT����萔���ŒT���������������y��
	int MakeHash(const char* string)
	{
		int hash = 0;
		int l = (int)strlen(string);
		for (int i = 0; i < l; i++){
			hash = hash * 37 + string[i];
		}
		return hash;
	}
}

EffectManager::EffectManager()
{

}

EffectManager::~EffectManager()
{
	Release();
}

//�n���ꂽX�t�@�C������G�t�F�N�g�����[�h���ۑ�����
LPD3DXEFFECT EffectManager::LoadEffect(const char* filePath)
{

	LPD3DXEFFECT effect = nullptr;
	int hash = MakeHash(filePath);

	//find�͎w�肵���L�[�ŗv�f��T��
	auto it = m_effectDictinary.find(hash);
	//end�͖������w���C�e���[�^���擾����
	if (it == m_effectDictinary.end()) {
		//�V�K�B
		LPD3DXBUFFER  compileErrorBuffer = nullptr;
		HRESULT hr = D3DXCreateEffectFromFile(
			g_pd3dDevice,	//�G�t�F�N�g���쐬����f�o�C�X�ւ̃|�C���^
			filePath,		//�t�@�C�����ւ̃p�X�A���̈����́AUnicode�������ANSI������̗������T�|�[�g���Ă���
			NULL,			//�v���v���Z�b�T�}�N����`��NULL�ŏI���I�v�V�����̔z��
			NULL,			//���̒l��NULL���w�肷��ƁA#includes�̓t�@�C������R���p�C������ꍇ�͗L�������A���\�[�X�⃁��������R���p�C������ꍇ�̓G���[�ƂȂ�
//�V�F�[�_���R���p�C������ۂ̃R���p�C�� �I�v�V�����𐧌䂷��
#ifdef _DEBUG
			D3DXSHADER_DEBUG,	//�V�F�[�_�̃R���p�C�����ɁA�f�o�b�O�t�@�C�����ƍs�ԍ���}������B
#else
			D3DXSHADER_SKIPVALIDATION,	//�������ꂽ�R�[�h�ɑ΂��Ċ��m�̔\�͂���ѐ���̌��؂����Ȃ��B���̃I�v�V�����́A���삷�邱�Ƃ��킩���Ă���V�F�[�_���R���p�C������ꍇ(�܂�A�O�ɂ��̃I�v�V�������g�킸�ɃV�F�[�_���R���p�C���������Ƃ�����ꍇ) �ɂ̂ݎg�p���邱�Ƃ����߂�
#endif
			NULL,				//���L�����Ŏg��ID3DXEffectPool�I�u�W�F�N�g�ւ̃|�C���^�A���̒l��NULL���w�肷��ƁA�����͋��L����Ȃ�
			&effect,			//�R���p�C�����ꂽ�G�t�F�N�g���i�[���ꂽ�o�b�t�@�ւ̃|�C���^��Ԃ�
			&compileErrorBuffer	//�R���p�C���G���[�̈ꗗ���i�[���ꂽ�o�b�t�@�ւ̃|�C���^��Ԃ�
			);
		if (FAILED(hr)) {
			MessageBox(nullptr, reinterpret_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
			//�ǂݍ��ݎ��s�B
			std::abort();
		}

		//�L�[�ƒl(effect)���y�A�ň���
		std::pair<int, LPD3DXEFFECT> node(hash, effect);
		//insert�͗v�f��}������
		m_effectDictinary.insert(node);
	}
	else {
		//�o�^�ς�
		//first��(�L�[�̒l)�Asecond��(���g=�G�t�F�N�g�t�@�C���̃|�C���^)
		effect = it->second;
	}
	return effect;
}
/*!
* @brief	�����[�X�B
*/
void EffectManager::Release()
{
	for (auto p : m_effectDictinary) {
		p.second->Release();;
	}
	//�S�Ă̗v�f���폜����
	m_effectDictinary.clear();
}