/*!
* @brief	ユーティリティ関数。
*/
#ifndef _TKUTIL_H_
#define _TKUTIL_H_

class CUtil {
public:
	//文字列から32bitのハッシュ値を作成。
	//ハッシュ値を作る理由は文字列で探すより数字で探した方が処理が軽い。
	static int MakeHash(const char* string)
	{
		int hash = 0;
		int l = (int)strlen(string);
		for (int i = 0; i < l; i++) {
			hash = hash * 37 + string[i];
		}
		return hash;
	}
};


#endif // _TKUTIL_H_