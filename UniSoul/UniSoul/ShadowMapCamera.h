#pragma once

class UnityChan;

//シャドウmマップカメラクラス。
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

	//ビュー行列の設定。
	void SetShadowMapCameraViewMatrix(D3DXMATRIX View)
	{
		m_shadowmapcameraviewMatrix = View;
	}

	//ビュー行列の取得。
	D3DXMATRIX GetShadowMapCameraViewMatrix()
	{
		return m_shadowmapcameraviewMatrix;
	}

	//プロジェクション行列の設定。
	void SetShadowMapCameraProjectionMatrix(D3DXMATRIX Proj)
	{
		m_shadowmapcameraprojectionMatrix = Proj;
	}

	//プロジェクション行列の取得。
	D3DXMATRIX GetShadowMapCameraProjectionMatrix()
	{
		return m_shadowmapcameraprojectionMatrix;
	}

	//カメラの座標の設定。
	void SetShadowMapCameraEyePt(D3DXVECTOR3 Eye)
	{
		m_shadowmapcameraeyePt = Eye;
	}

	//カメラの座標の取得。
	D3DXVECTOR3 GetShadowMapCameraEyePt()
	{
		return m_shadowmapcameraeyePt;
	}

	//カメラの注視点の設定。
	void SetShadowMapCameraLooktPt(D3DXVECTOR3 Lookat)
	{
		m_shadowmapcameralookatPt = Lookat;
	}

	//カメラの注視点の取得。
	D3DXVECTOR3 GetShadowMapCameraLooktPt()
	{
		return m_shadowmapcameralookatPt;
	}

	//カメラの上方向の設定。
	void SetShadowMapCameraUpVec(D3DXVECTOR3 Up)
	{
		m_shadowmapcameraupvec = Up;
	}

	//カメラの上方向の取得。
	D3DXVECTOR3 GetShadowMapCameraUpVec()
	{
		return m_shadowmapcameraupvec;
	}

	//ファーの設定。
	void SetShadowMapCameraFar(float Far)
	{
		m_shadowmapcamerafar = Far;
	}

	//ファーの取得。
	float GetShadowMapCameraFar()
	{
		return m_shadowmapcamerafar;
	}

	//二アーの設定。
	void SetNear(float Near)
	{
		m_shadowmapcameranear = Near;
	}

	//二アーの取得。
	float GetShadowMapCameraNear()
	{
		return m_shadowmapcameranear;
	}

	//アスペクト比の設定。
	void SetShadowMapCameraAspect(float Aspect)
	{
		m_shadowmapcameraaspect = Aspect;
	}

	//アスペクト比の取得。
	float GetShadowMapCameraAspect()
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
	UnityChan*      m_unitychan;						//ユニティちゃんのインスタンス。
};