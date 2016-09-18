#ifndef DRAWEVENT_H
#define DRAWEVENT_H

#include <d3dx9.h>

// 各エフェクトビット(|で複合, &で識別)
#define DEE_BILLBOARD	0x00000001
#define DEE_SKYBOX		0x00000002
#define DEE_SEASERFACE	0x00000004
#define DEE_4			0x00000008
#define DEE_5			0x00000010

// アルファ値(下1バイトは0~255のアルファ値)
#define DEA_NORMAL		0x00000000
#define DEA_ADDITION	0x00001000
#define DEA_REDUCE		0x00002000

//=============================================================
// SDrawEvent
//-------------------------------------------------------------
// 描画オブジェクトを描画するイベント。
// 描画イベントキューに保存されて毎フレームごとに解決する。
// 3Dオブジェクト、スプライト、テキスト
//=============================================================
typedef struct _SDrawEvent
{
	// 描画オブジェクトID
	int objectID;
	// ワールド行列
	D3DXMATRIXA16 matWorld;
	// アルファ値
	int alpha;
	// エフェクト
	int effect;
	// 次のイベント
	struct _SDrawEvent* next;
} SDrawEvent;

//=============================================================
// CDrawEventStack
//-------------------------------------------------------------
// 描画イベントを保持するキュークラス
//=============================================================
class CDrawEventStack
{
public:
	// 末尾にイベントの追加
	void Push(SDrawEvent &ev);
	// 先頭のイベントの削除
	void Pop();
	// 先頭のイベントの取得
	SDrawEvent* GetFront();

	// キューの作成(最大イベント数)
	void Create(int max_num_event);
	// イベントのクイックソート
	void Sort();
	// キューのクリア
	void Clear();
	// 空か
	bool Empty();
private:
	SDrawEvent* queue;
	SDrawEvent* active;
	SDrawEvent* free;
};

#endif
