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

	//モデルデータのクローンを作成。
	//スケルトンは新しく作成され、メッシュデータは共通のものが使用されます。
	void CloneModelData(const SkinModelData& modelData, Animation* anim);

	//オリジナルのスケルトンを削除。
	//@param[in]	frame	スケルトン。
	void DeleteSkeleton(LPD3DXFRAME frame);

	//スケルトンのクローンを削除。
	//@param[in]	frame		削除するスケルトン。
	void DeleteCloneSkeleton(LPD3DXFRAME frame);

	//スケルトンのクローンを作成。
	//@param[out]	dstFrame		クローン先のスケルトンの格納先。
	//@param[in]		srcFrame		クローン元のスケルトン。
	void CloneSkeleton(LPD3DXFRAME& dstFrame, LPD3DXFRAME srcFrame);

	//クローンしたアニメーションコントローラーは何もしていないのでオリジナルのフレームルートを指している。
	//なのでクローンのアニメーションコントローラーをクローンスケルトンのフレームルートを指すようする必要がある。
	//それがこの処理。
	void SetupOutputAnimationRegist(LPD3DXFRAME frame, ID3DXAnimationController* animCtr);

	void Release();
private:
	LPD3DXFRAME					m_frameRoot;		//フレームルート。
	ID3DXAnimationController*   m_pAnimController;	//アニメーションコントローラ。
	bool						m_isClone;			//クローン。
};