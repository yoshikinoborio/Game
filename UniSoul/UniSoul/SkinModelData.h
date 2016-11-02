#pragma once
struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//合成済み行列。
};
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
	LPDIRECT3DTEXTURE9* ppTextures;
	LPD3DXMESH pOrigMesh;
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD NumAttributeGroups;
	DWORD NumInfl;
	LPD3DXBUFFER pBoneCombinationBuf;
	D3DXMATRIX** ppBoneMatrixPtrs;
	D3DXMATRIX* pBoneOffsetMatrices;
	DWORD NumPaletteEntries;
	bool UseSoftwareVP;
	DWORD iAttributeSW;
};
class Animation;

//スキンモデルデータクラス
class SkinModelData{
public:
	SkinModelData();
	~SkinModelData();
	
	//モデルデータをロード
	//filePath	ファイルパス
	//anim		アニメーション付きモデルデータの場合、アニメーションクラスも構築される
	void LoadModelData(const char* filePath, Animation* anim);

	//フレームルートの取得
	LPD3DXFRAME GetFrameRoot()
	{
		return m_frameRoot;
	}

	//アニメーションコントローラーの取得
	ID3DXAnimationController* GetAnimationController()
	{
		return m_pAnimController;
	}

	//一番最初に見つかったオリジナルメッシュを取得。
	LPD3DXMESH GetOrgMeshFirst();

	//一番最初に見つかったオリジナルメッシュを取得。
	LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame);

	//ルートのボーンを取得。
	D3DXMATRIX* GetRootBoneWorldMatrix()
	{
		D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)m_frameRoot;
		return &frameDer->CombinedTransformationMatrix;
	}

	//ボーン行列の更新
	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);

	void Release();
private:
	LPD3DXFRAME					m_frameRoot;		//フレームルート。
	ID3DXAnimationController*   m_pAnimController;	//アニメーションコントローラ。
};
