#include "stdafx.h"
#include "EffectManager.h"

namespace{
	
	//文字列から32bitのハッシュ値を作成。
	//ハッシュ値を作る理由は文字列で探すより数字で探した方が処理が軽い
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

//渡されたXファイルからエフェクトをロードし保存する
LPD3DXEFFECT EffectManager::LoadEffect(const char* filePath)
{

	LPD3DXEFFECT effect = nullptr;
	int hash = MakeHash(filePath);

	//findは指定したキーで要素を探す
	auto it = m_effectDictinary.find(hash);
	//endは末尾を指すイテレータを取得する
	if (it == m_effectDictinary.end()) {
		//新規。
		LPD3DXBUFFER  compileErrorBuffer = nullptr;
		HRESULT hr = D3DXCreateEffectFromFile(
			g_pd3dDevice,	//エフェクトを作成するデバイスへのポインタ
			filePath,		//ファイル名へのパス、この引数は、Unicode文字列とANSI文字列の両方をサポートしている
			NULL,			//プリプロセッサマクロ定義のNULLで終わるオプションの配列
			NULL,			//この値にNULLを指定すると、#includesはファイルからコンパイルする場合は有効だが、リソースやメモリからコンパイルする場合はエラーとなる
//シェーダをコンパイルする際のコンパイル オプションを制御する
#ifdef _DEBUG
			D3DXSHADER_DEBUG,	//シェーダのコンパイル時に、デバッグファイル名と行番号を挿入する。
#else
			D3DXSHADER_SKIPVALIDATION,	//生成されたコードに対して既知の能力および制約の検証をしない。このオプションは、動作することがわかっているシェーダをコンパイルする場合(つまり、前にこのオプションを使わずにシェーダをコンパイルしたことがある場合) にのみ使用することを勧める
#endif
			NULL,				//共有引数で使うID3DXEffectPoolオブジェクトへのポインタ、この値にNULLを指定すると、引数は共有されない
			&effect,			//コンパイルされたエフェクトが格納されたバッファへのポインタを返す
			&compileErrorBuffer	//コンパイルエラーの一覧が格納されたバッファへのポインタを返す
			);
		if (FAILED(hr)) {
			MessageBox(nullptr, reinterpret_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
			//読み込み失敗。
			std::abort();
		}

		//キーと値(effect)をペアで扱う
		std::pair<int, LPD3DXEFFECT> node(hash, effect);
		//insertは要素を挿入する
		m_effectDictinary.insert(node);
	}
	else {
		//登録済み
		//firstは(キーの値)、secondは(中身=エフェクトファイルのポインタ)
		effect = it->second;
	}
	return effect;
}
/*!
* @brief	リリース。
*/
void EffectManager::Release()
{
	for (auto p : m_effectDictinary) {
		p.second->Release();;
	}
	//全ての要素を削除する
	m_effectDictinary.clear();
}