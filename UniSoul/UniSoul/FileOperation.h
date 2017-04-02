#pragma once

//バイナリファイルの入出力を行うクラス。
class FileOperation
{
public:
	//コンストラクタ。
	FileOperation();

	//デストラクタ。
	~FileOperation();

	//バイナリファイルに吐き出す処理。
	void OutPutText(const D3DXVECTOR3& pos);

	//バイナリファイルから情報を取得する処理。
	const D3DXVECTOR3& ReadText() const;
};