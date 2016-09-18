#ifndef SCENEDEMO_H
#define SCENEDEMO_H

#include "SceneBase.h"

//=============================================================
// CSceneDemo
//-------------------------------------------------------------
// タイトル画面移行前のデモシーン。
// ボタンを押すとショートカットできる。
//=============================================================
class CSceneDemo : public CSceneBase
{
public:
	CSceneDemo();
	~CSceneDemo();

	void Update();
	void Draw();
	void Init(CSystemScene *_system);
	void UnInit();
private:
	// 背景ID
	int starID;

	int fontID;
	char string[256];
	D3DCOLOR color;
	D3DBLEND blend;
	BOOL bill;
	D3DXMATRIXA16 mat, mat2;

	// パーティクル位置配列
	D3DXVECTOR2 vecParticlePos[32];
	// パーティクル拡大率
	float particleScaling[32];

	int time;
};


#endif