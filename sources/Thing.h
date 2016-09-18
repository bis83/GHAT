#ifndef THING_H
#define THING_H

#include <d3dx9.h>
#include "DrawObject.h"
#include "HandleSystem.h"

//=============================================================
// CThing
//-------------------------------------------------------------
// 物クラスの基底クラス。
// オブジェクトを描画する際に必要なステータスを分かりやすく持つ。
//=============================================================
class CThing
{
public:
	CThing();

	// グラフィックスへのポインタを渡すと描画処理を行う
	virtual void DrawThing(CHandleGraphics* hGrap) = 0;
	// 初期セットアップ
	virtual void Set(const char* filename, CHandleGraphics* hGrap) = 0;

	// 初期化
	void InitMatrix();
	// 3種類のベクトルから行列を更新する
	void SetMatrix();

	// オブジェクトID
	int objectID;
	// ワールド行列
	D3DXVECTOR3 vecPos;
	D3DXVECTOR3 vecScale;
	D3DXVECTOR3 vecRot;
	D3DXMATRIXA16 matWorld;
};

//=============================================================
// CThingMesh
//-------------------------------------------------------------
// メッシュ用の情報を追加した物クラス。
//=============================================================
class CThingMesh : public CThing
{
public:
	CThingMesh();

	void DrawThing(CHandleGraphics *hGrap);
	void Set(const char* filename, CHandleGraphics *hGrap);

	// ブレンドタイプ(0:通常,1:加法)
	int blendType;
	// ビルボードフラグ
	bool billBoarding;
	// カリングモード(0:NONE, 1:CW, 2:CCW)
	int culling;
	// シェーディングモード(0:グーロー,1:フラット)
	int shadeMode;
	// フィルモード(0:ソリッド, 1:ワイヤフレーム, 2:ポイント)
	int fillMode;
	// エフェクト(未実装)
	int effectMode;
};

//=============================================================
// CThingSprite
//-------------------------------------------------------------
// スプライト用の情報を追加した物クラス。
//=============================================================
class CThingSprite : public CThing
{
public:
	CThingSprite();

	void DrawThing(CHandleGraphics *hGrap);
	void Set(const char *filename, CHandleGraphics *hGrap);

	BYTE a, r, g, b;
	// ブレンドタイプ(0:通常,1:加法)
	int blendType;
	// ビルボード
	BOOL billBoard;
};

#endif