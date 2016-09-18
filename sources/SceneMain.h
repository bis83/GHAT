#ifndef SCENEMAIN_H
#define SCENEMAIN_H

#include "SceneBase.h"
#include "StageScript.h"

//=============================================================
// CSceneMain
//-------------------------------------------------------------
// ゲームのメインシーン。
//=============================================================
class CSceneMain : public CSceneBase
{
public:
	CSceneMain();
	~CSceneMain();

	void Update();
	void Draw();
	void Init(CSystemScene* _system);
	void UnInit();
private:
	// フォントID
	int fontID;
	// 文字列
	char string[32];
	// 行列
	D3DXMATRIXA16 mat;

	// アイテム取得音
	int itemGetID;

	// ポーズフラグ
	bool pause_f;

	int wait;
	bool gameover;

	// ステージスクリプト
	CStageScript script;
};

#endif