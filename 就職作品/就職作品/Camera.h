#pragma once

class Player;

//カメラクラス
class Camera
{
public:
	//コンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//初期化
	void Initialize();

	//更新
	void Update();

	//ビュー行列の設定
	void SetViewMatrix(D3DXMATRIX View)
	{
		m_viewMatrix = View;
	}

	//ビュー行列の取得
	D3DXMATRIX GetViewMatrix()
	{
		return m_viewMatrix;
	}

	//プロジェクション行列の設定
	void SetProjectionMatrix(D3DXMATRIX Proj)
	{
		m_projectionMatrix = Proj;
	}

	//プロジェクション行列の取得
	D3DXMATRIX GetProjectionMatrix()
	{
		return m_projectionMatrix;
	}

	//カメラの座標の設定
	void SetEyePt(D3DXVECTOR3 Eye)
	{
		m_eyePt = Eye;
	}
	
	//カメラの座標の取得
	D3DXVECTOR3 GetEyePt()
	{
		return m_eyePt;
	}

	//カメラの注視点の設定
	void SetLookatPt(D3DXVECTOR3 Lookat)
	{
		m_lookatPt = Lookat;
	}
	
	//カメラの注視点の取得
	D3DXVECTOR3 GetLookatPt()
	{
		return m_lookatPt;
	}

	//カメラの上方向の設定
	void SetUpVec(D3DXVECTOR3 Up)
	{
		m_upVec = Up;
	}
	
	//カメラの上方向の取得
	D3DXVECTOR3 GetUpVec()
	{
		return m_upVec;
	}

	//ファーの設定
	void SetFar(float Far)
	{
		m_far = Far;
	}

	//ファーの取得
	float GetFar()
	{
		return m_far;
	}

	//二アーの設定
	void SetNear(float Near)
	{
		m_near = Near;
	}

	//二アーの取得
	float GetNear()
	{
		return m_near;
	}

	//アスペクト比の設定
	void SetAspect(float Aspect)
	{
		m_aspect = Aspect;
	}

	//アスペクト比の取得
	float GetAspect()
	{
		return m_aspect;
	}
private:
	D3DXMATRIX		m_viewMatrix;			//ビュー行列 カメラ行列とも言う
	D3DXMATRIX		m_projectionMatrix;		//プロジェクション行列 ビュー空間から射影空間に変換する行列
	D3DXVECTOR3		m_eyePt;				//カメラの座標
	D3DXVECTOR3		m_lookatPt;				//カメラの注視点
	D3DXVECTOR3		m_upVec;				//カメラの上方向
	float			m_far;					//遠平面(ファー)
	float			m_near;					//近平面(ニアー)
	float			m_aspect;				//アスペクト比
	D3DXVECTOR3		m_toEyeptVector;		//注視点からカメラの座標に向かうベクトル
	Player*			m_player;				//プレイヤーインスタンス
	float			m_angle;				//回転
	D3DXQUATERNION	m_yAxis;				//Y軸回転のクォータニオン
	D3DXMATRIX		m_rot;					//クォータニオンから作った回転行列を格納
	D3DXVECTOR4		m_v4;					//回転行列を使ってm_toEyeptVectorを回転させたのを格納
	float			m_rStick_x;				//右スティックのX軸の入力量を格納
	float           m_rStick_y;				//右スティックのY軸の入力量を格納
};