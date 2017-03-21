#pragma once
#include "CharacterController.h"
class UnityChan;

//カメラクラス
class Camera
{
public:
	enum class GameObject
	{
		Skeleton = 0,
		Goblin,
		House_A,
		House_B,
		House_C,
		House_D,
		Yashi,
		ObjectNum,
	};
	//コンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//初期化
	void Initialize();

	//更新
	void Update();

	//パッドを使ったカメラの回転の処理。
	void PadUseRotation();

	//フリーカメラモードの処理。
	void FreeCameraMode();

	//フリーカメラモードフラグの操作処理。
	void FreeCameraFlagChanger();

	//ゲームの停止。
	void GameStop();

	//カメラのビュー行列とパースペクティブ射影行列の作成。
	void CameraMatrixUpadate();

	//カメラがプレイヤーを追いかける処理。
	void TargetPlayer();

	//ゲームの終了。
	void GameEnd();


	//ビュー行列の設定
	void SetViewMatrix(const D3DXMATRIX& View)
	{
		m_viewMatrix = View;
	}

	//ビュー行列の取得
	const D3DXMATRIX& GetViewMatrix() const
	{
		return m_viewMatrix;
	}

	//ビュー行列の逆行列を取得。
	const D3DXMATRIX& GetViewMatrixInv() const
	{
		return m_viewMatrixInv;
	}

	//プロジェクション行列の設定
	void SetProjectionMatrix(const D3DXMATRIX& Proj)
	{
		m_projectionMatrix = Proj;
	}

	//プロジェクション行列の取得
	const D3DXMATRIX& GetProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

	//カメラの座標の設定
	void SetEyePt(const D3DXVECTOR3& Eye)
	{
		m_eyePt = Eye;
	}
	
	//カメラの座標の取得
	const D3DXVECTOR3& GetEyePt() const
	{
		return m_eyePt;
	}

	//カメラの注視点の設定
	void SetLookatPt(const D3DXVECTOR3& Lookat)
	{
		m_lookatPt = Lookat;
	}
	
	//カメラの注視点の取得
	const D3DXVECTOR3& GetLookatPt() const
	{
		return m_lookatPt;
	}

	//カメラの上方向の設定
	void SetUpVec(const D3DXVECTOR3& Up)
	{
		m_upVec = Up;
	}
	
	//カメラの上方向の取得
	const D3DXVECTOR3& GetUpVec() const
	{
		return m_upVec;
	}

	//ファーの設定
	void SetFar(float Far)
	{
		m_far = Far;
	}

	//ファーの取得
	float GetFar() const
	{
		return m_far;
	}

	//二アーの設定
	void SetNear(float Near)
	{
		m_near = Near;
	}

	//二アーの取得
	float GetNear() const
	{
		return m_near;
	}

	//アスペクト比の設定
	void SetAspect(float Aspect)
	{
		m_aspect = Aspect;
	}

	//アスペクト比の取得
	float GetAspect() const
	{
		return m_aspect;
	}
	//カメラのが自由か固定かのフラグを取得。
	bool GetCameraFreeFlag() const
	{
		return m_cameraFreeFlag;
	}

	int GetNowObject() const
	{
		return m_nowGameObject;
	}
private:
	D3DXMATRIX		m_viewMatrix;			//ビュー行列 カメラ行列とも言う。
	D3DXMATRIX		m_projectionMatrix;		//プロジェクション行列 ビュー空間から射影空間に変換する行列・
	D3DXMATRIX		m_viewMatrixInv;		//ビュー行列の逆行列。
	D3DXVECTOR3		m_eyePt;				//カメラの座標。
	D3DXVECTOR3		m_lookatPt;				//カメラの注視点。
	D3DXVECTOR3		m_upVec;				//カメラの上方向。
	float			m_far;					//遠平面(ファー)。
	float			m_near;					//近平面(ニアー)。
	float			m_aspect;				//アスペクト比。
	D3DXVECTOR3		m_toEyeptVector;		//注視点からカメラの座標に向かうベクトル。
	UnityChan*      m_unitychan;			//プレイヤーのインスタンス。
	float			m_angle;				//回転。
	D3DXQUATERNION	m_yAxis;				//Y軸回転のクォータニオン。
	D3DXQUATERNION	m_zAxis;				//Z軸回転のクォータニオン。
	D3DXMATRIX		m_rot;					//クォータニオンから作った回転行列を格納。
	D3DXVECTOR4		m_v4;					//回転行列を使ってm_toEyeptVectorを回転させたのを格納。
	float			m_rStick_x;				//右スティックのX軸の入力量を格納。
	float           m_rStick_y;				//右スティックのY軸の入力量を格納。
	bool			m_cameraFreeFlag;		//自由なカメラに切り替えるフラグ。
	D3DXVECTOR3     m_moveDir;				//カメラの向き。
	int				m_nowGameObject;		//選択されているゲームオブジェクト。
	DWORD			m_nowTime;				//現在の時間を格納。
	DWORD			m_selectMoveTime;		//オブジェクトを選択してから経過した時間。
};