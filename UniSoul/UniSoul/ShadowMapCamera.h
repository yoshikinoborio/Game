#pragma once

class UnityChan;

//シャドウマップカメラクラス。
class ShadowMapCamera
{
public:
	//コンストラクタ。
	ShadowMapCamera();

	//デストラクタ。
	~ShadowMapCamera();

	//初期化。
	void Initialize();

	//更新。
	void Update();

	//シャドウカメラのビュー行列とパースペクティブ射影行列の作成。
	void ShadowCameraMatrixUpadate();

	//シャドウカメラがプレイヤーを追いかける処理。
	void ShadowCameraTargetPlayer();

	//ビュー行列の設定。
	void SetShadowMapCameraViewMatrix(const D3DXMATRIX& View)
	{
		m_shadowmapcameraviewMatrix = View;
	}

	//ビュー行列の取得。
	const D3DXMATRIX& GetShadowMapCameraViewMatrix() const
	{
		return m_shadowmapcameraviewMatrix;
	}

	//プロジェクション行列の設定。
	void SetShadowMapCameraProjectionMatrix(const D3DXMATRIX& Proj)
	{
		m_shadowmapcameraprojectionMatrix = Proj;
	}

	//プロジェクション行列の取得。
	const D3DXMATRIX& GetShadowMapCameraProjectionMatrix() const
	{
		return m_shadowmapcameraprojectionMatrix;
	}

	//カメラの座標の設定。
	void SetShadowMapCameraEyePt(const D3DXVECTOR3& Eye)
	{
		m_shadowmapcameraeyePt = Eye;
	}

	//カメラの座標の取得。
	const D3DXVECTOR3& GetShadowMapCameraEyePt() const
	{
		return m_shadowmapcameraeyePt;
	}

	//カメラの注視点の設定。
	void SetShadowMapCameraLooktPt(const D3DXVECTOR3& Lookat)
	{
		m_shadowmapcameralookatPt = Lookat;
	}

	//カメラの注視点の取得。
	const D3DXVECTOR3& GetShadowMapCameraLooktPt() const
	{
		return m_shadowmapcameralookatPt;
	}

	//カメラの上方向の設定。
	void SetShadowMapCameraUpVec(const D3DXVECTOR3& Up)
	{
		m_shadowmapcameraupvec = Up;
	}

	//カメラの上方向の取得。
	const D3DXVECTOR3& GetShadowMapCameraUpVec() const
	{
		return m_shadowmapcameraupvec;
	}

	//ファーの設定。
	void SetShadowMapCameraFar(const float& Far)
	{
		m_shadowmapcamerafar = Far;
	}

	//ファーの取得。
	const float& GetShadowMapCameraFar() const
	{
		return m_shadowmapcamerafar;
	}

	//二アーの設定。
	void SetNear(const float& Near)
	{
		m_shadowmapcameranear = Near;
	}

	//二アーの取得。
	const float& GetShadowMapCameraNear() const
	{
		return m_shadowmapcameranear;
	}

	//アスペクト比の設定。
	void SetShadowMapCameraAspect(const float& Aspect)
	{
		m_shadowmapcameraaspect = Aspect;
	}

	//アスペクト比の取得。
	const float& GetShadowMapCameraAspect() const
	{
		return m_shadowmapcameraaspect;
	}
private:
	D3DXMATRIX		m_shadowmapcameraviewMatrix;		//シャドウカメラのビュー行列 カメラ行列とも言う。
	D3DXMATRIX		m_shadowmapcameraprojectionMatrix;	//シャドウカメラのプロジェクション行列 ビュー空間から射影空間に変換する行列。
	D3DXVECTOR3		m_shadowmapcameraeyePt;				//シャドウカメラの座標。
	D3DXVECTOR3		m_shadowmapcameralookatPt;			//シャドウカメラの注視点。
	D3DXVECTOR3		m_shadowmapcameraupvec;				//シャドウカメラの上方向。
	float			m_shadowmapcamerafar;				//シャドウカメラの遠平面(ファー)。
	float			m_shadowmapcameranear;				//シャドウカメラの近平面(ニアー)。
	float			m_shadowmapcameraaspect;			//シャドウカメラのアスペクト比。
	D3DXVECTOR3		m_toEyeptVector;					//注視点からカメラの座標に向かうベクトル。
	UnityChan*      m_unitychan;						//プレイヤーのインスタンス。
};