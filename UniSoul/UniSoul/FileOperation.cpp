#include "stdafx.h"
#include "FileOperation.h"
#include <fstream>
using namespace std;

//プレイヤーが最後にセーブした位置を格納する。
namespace {
	struct PlayerDateInfo
	{
		D3DXVECTOR3 pos = { 100.0f,100.0f,100.0f };	//プレイヤーが最後に到達したセーブポイント。
	}SaveDate;
}

//コンストラクタ。
FileOperation::FileOperation()
{
}

//デストラクタ。
FileOperation::~FileOperation()
{
}

//バイナリファイルに吐き出す処理。
void FileOperation::OutPutText(const D3DXVECTOR3& pos)
{
	SaveDate.pos = pos;

	//読み込むファイルと操作するモードを指定。
	FILE *fp = fopen("PlayerRespawnPosition.dat", "wb");//バイナリファイルを開く。
	if (fp == NULL) {//エラーが起きたらNULLを返す。
		OutputDebugString("ファイルが読み込めなかった。");
	}
	else
	{
		//第一引数が、セーブデータを持った変数のアドレス。
		//第二引数が、出力するバイト数。
		//第三引数が、出力する個数。
		//第四引数が、出力するファイルポインタ。
		fwrite(&SaveDate, sizeof(SaveDate), 1, fp); // SaveData構造体の中身を出力。
		fclose(fp);//ファイルを閉じる。
	}

}

//バイナリファイルから情報を取得する処理。
const D3DXVECTOR3& FileOperation::ReadText() const
{
	//読み込むファイルと操作するモードを指定。
	FILE *fp = fopen("PlayerRespawnPosition.dat", "rb");//バイナリファイルを開く。
	if (fp == NULL) {
		OutputDebugString("ファイルが読み込めなかった。");
	}
	else
	{
		//バイナリに吐き出した情報を読み込む。
		fread(&SaveDate, sizeof(SaveDate), 1, fp);
		fclose(fp);
		return SaveDate.pos;
	}
	
}
