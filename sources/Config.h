#ifndef CONFIG_H
#define CONFIG_H

//=============================================================
// CConfig
//-------------------------------------------------------------
// コンフィグの情報を扱うクラス。
//=============================================================
class CConfig
{
public:
	// コンストラクタ
	CConfig();

	// ファイルからの読み込み
	void LoadFile();
	// ファイルへの書き出し
	void SaveFile();

	int key_ok;
	int key_cancel;
	int key_shot;
	int key_bomb;
	int key_pause;
	int bgm_volume;
	int se_volume;
	int rest;
	int difficult;
};

extern CConfig e_Config;

#endif
