#ifndef SCENEGAMEOVER_H
#define SCENEGAMEOVER_H

#include "SystemScene.h"
#include "SceneBase.h"

//=============================================================
// CSceneGameOver
//-------------------------------------------------------------
// ゲームオーバー及びネームエントリーシーン。
//=============================================================
class CSceneGameOver : public CSceneBase
{
public:
	CSceneGameOver();
	~CSceneGameOver();

	void Update();
	void Draw();
	void Init(CSystemScene *_system);
	void UnInit();
private:
	// フォントID
	int fontID;

	// 星ID
	int planetID;
	// ゲームオーバー画像ID
	int overID;
	D3DXMATRIXA16 mat;
	D3DCOLOR color;
	D3DFILLMODE fill;

	// カーソル音ID
	int cursorID;
	// 決定音ID
	int decideID;
	// キャンセル音ID
	int cancelID;

	// オーバー音ID
	int overSeID;
	// ネームエントリー音楽
	int entryBgmID;

	// フェーズ
	int phase;
	// ウェイト
	int wait;
	// ネーム
	char name[4];
	int score;
	int rank;
	// 名前の何文字目の入力か？
	int nameIndex;
	// 文字選択インデックス
	int index;
	// 文字テーブル
	char charTable[64+1];
};

#endif