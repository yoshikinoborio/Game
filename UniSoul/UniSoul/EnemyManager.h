#pragma once
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
		bool isShadowReceiver);
	void Release();
private:
};