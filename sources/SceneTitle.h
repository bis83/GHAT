#ifndef SCENETITLE_H
#define SCENETITLE_H

#include "SceneBase.h"

//=============================================================
// CSceneTitle
//-------------------------------------------------------------
// タイトル及びコンフィグとランキングシーン。
// メイン以外のほぼ全て？
//=============================================================
class CSceneTitle : public CSceneBase
{
public:
	CSceneTitle();
	~CSceneTitle();

	void Update();
	void Draw();
	void Init(CSystemScene *_system);
	void UnInit();
private:
	// フェーズ(0:タイトル, 1:コンフィグ, 2:ランキング)
	int phase;
	// ステップ(フェーズ中のさらなる分岐用)
	int step;
	// 選択肢用
	int index;
	// ウェイト変数
	int wait;
	// 経過時間変数
	int time;
	// デモに戻る用
	int demo_time;

	// 背景ID
	int backID;
	// タイトルのID
	int titleID;
	// メニューのID
	int menuID[4];
	// フォントID
	int fontID;
	// パーティクル
	int particleID;

	// 決定SE
	int decideID;
	// キャンセルSE
	int cancelID;
	// カーソルSE
	int cursorID;

	// BGMID
	int bgmID;

	// 汎用マトリックス
	D3DXMATRIXA16 mat;
	D3DXMATRIXA16 mat2;
	// 汎用カラー
	D3DCOLOR color;
	// 汎用ブレンド
	D3DBLEND blend;
	// 汎用文字列
	char string[256];
	// パーティクル位置配列
	D3DXVECTOR2 vecParticlePos[32];
	// パーティクル拡大率
	float particleScaling[32];
};

#endif