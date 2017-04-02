#pragma once
#include "SkinModel.h"
#include "Turn.h"
#include "RigidBody.h"
#include "MeshCollider.h"
#include "DamageCollisionWorld.h"
#include "Light.h"
#include "CreateViewAngle.h"
#include "CharacterController.h"


//アニメーションする3Dモデルの基底クラス。
class AnimationModel3D
{
public:
	//コンストラクタ。
	AnimationModel3D();

	//デストラクタにVirtuaを付ける理由は
	//派生クラスのデストラクタが呼ばれずメモリリークが起きるから付けている。
	virtual~AnimationModel3D() 
	{
	}

	//純粋仮想関数はある基底クラス内のメソッドを派生クラス内で必ず実装(定義)してもらいたい場合、純粋仮想関数で宣言する。
	//純粋仮想関数で宣言されたクラスを継承する場合、必ずオーバーライドしなければならない。
	//基底クラスのメンバメソッドを継承クラスで変更する事ができる。簡単に言えば、再定義するという事。
	//この基底クラスの関数(オーバーライドされる関数)を仮想関数と言う。
	virtual void Update() = 0;
protected:
	SkinModelData*			m_skinModelData;			//スキンモデルデータ。
	SkinModel				m_skinModel;				//スキンモデル。
	Animation				m_animation;				//アニメーション。
	Turn					m_turn;						//回転処理。
	MeshCollider			m_meshCollider;				//メッシュコライダー。
	RigidBody				m_rigidBody;				//剛体。
	Light					m_light;					//ライト。
	CreateViewAngle			m_CreateViewAngle;			//視野角作成クラス。
	D3DXVECTOR3				m_position;					//座標。
	D3DXVECTOR3				m_scale;					//スケール。
	D3DXMATRIX				m_world;					//ワールド行列。
	D3DXQUATERNION			m_rotation;					//回転行列。
	CharacterController		m_characterController;		//キャラクタコントローラ。
	float					m_moveSpeed;				//移動速度(歩く時と走る時の速度調整用)。
	bool					m_isTurn;					//回転フラグ。
	float					m_height;					//キャラクターの高さ。
	float					m_radius;					//キャラクター敵の半径。
	int						m_hp;						//ヒットポイント。
	int						m_maxhp;					//最大ヒットポイント。
	float					m_currentAngleY;			//現在の方向。
	float					m_targetAngleY;				//向きたい方向。
	D3DXVECTOR3				m_move;						//移動量。
	bool					m_isDead;					//死んだ。
	float					m_frameDeltaTime = 1.0f / 60.0f;	//1フレームの経過時間。
	float					m_deltaTimeMul = 1.0f;				//⊿タイムに乗算される値。
};