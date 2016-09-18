#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <d3dx9.h>

// 描画オブジェクトタイプ
#define DOT_MESH		1
#define DOT_SPRITE		2
#define DOT_FONT		3
#define DOT_ANIMESH		4

// 描画オブジェクトステータス
typedef enum _DOSTATUS {
	DOS_MATRIX = 1,
	DOS_SRCBLEND = 2,
	DOS_DESTBLEND = 3,
	DOS_BILLBOARD = 4,
	DOS_CULL = 5,
	DOS_SHADE = 6,
	DOS_FILL = 7,
	DOS_EFFECT = 8,
	DOS_COLOR = 9,
	DOS_SIZE = 10,
	DOS_STRING = 11,
} DOSTATUS;

//=============================================================
// CDrawObject
//-------------------------------------------------------------
// 描画オブジェクト。全てのオブジェクトの基底クラス。
// 名前とオブジェクトの種類を管理する。
//=============================================================
class CDrawObject
{
public:
	// 生成
	virtual void Create(const char* filename, LPDIRECT3DDEVICE9 pDevice) = 0;
	// 破棄
	virtual void Destroy() = 0;
	// オブジェクトタイプの取得
	int GetObjectType() { return objectType; }
	// 名前の取得
	LPSTR GetName() { return name; }
protected:
	int objectType;
	LPSTR name;
};

//=============================================================
// CObjectMesh
//-------------------------------------------------------------
// メッシュオブジェクト。
// アニメーションメッシュをサポートする。
//=============================================================
class CObjectMesh : public CDrawObject
{
public:
	// 生成
	void Create(const char* filename, LPDIRECT3DDEVICE9 pDevice);
	void Destroy();

	void ResetStatus();

	// フレームルート
	LPD3DXFRAME pFrameRoot;
	// メッシュ
	LPD3DXMESH pMesh;
	// アニメコントローラー
	LPD3DXANIMATIONCONTROLLER pAnimeController;
	// メッシュマテリアル
	D3DMATERIAL9* pMeshMaterials;
	// メッシュテクスチャ
	LPDIRECT3DTEXTURE9* pMeshTextures;
	// マテリアル総数
	DWORD dwNumMaterials;

	// ワールド行列
	D3DXMATRIXA16 matWorld;
	// ブレンドタイプ
	D3DBLEND srcBlend;
	D3DBLEND destBlend;
	// ビルボーディング
	BOOL billboarding;
	// カリング
	D3DCULL cullMode;
	// シェーディングモード
	D3DSHADEMODE shadeMode;
	// フィルモード
	D3DFILLMODE fillMode;
	// プログラブルシェーディング(未実装)
	int effectID;
};

//=============================================================
// CObjectSprite
//-------------------------------------------------------------
// スプライト用オブジェクト。
// テクスチャとスプライトの大きさと色を持つ。
//=============================================================
class CObjectSprite : public CDrawObject
{
public:
	void Create(const char* filename, LPDIRECT3DDEVICE9 pDevice);
	void Destroy();

	// サイズのセット
	void SetSize(int width, int height);

	void ResetStatus();

	// テクスチャ
	LPDIRECT3DTEXTURE9 pTexture;
	// 中心点
	D3DXVECTOR3 vecCenter;
	// 矩形
	RECT rect;

	// ワールド行列
	D3DXMATRIXA16 matWorld;
	// 色
	D3DCOLOR color;
	// ブレンドタイプ
	D3DBLEND srcBlend;
	D3DBLEND destBlend;
	// ビルボード
	BOOL billboarding;
};

//=============================================================
// CObjectFont
//-------------------------------------------------------------
// フォント用スプライトオブジェクト。
// フォントのテクスチャ画像と文字列を持つ。
//=============================================================
class CObjectFont : public CDrawObject
{
public:
	void Create(const char* filename, LPDIRECT3DDEVICE9 pDevice);
	void Destroy();

	void SetSize(int width, int height);

	void ResetStatus();

	// テクスチャ
	LPDIRECT3DTEXTURE9 pTexture;
	// 矩形
	RECT rect;
	// テクスチャ全体の大きさ
	int t_width, t_height;
	// フォントの種類
	int num_font;
	// 一文字の大きさ
	int c_width, c_height;
	// 文字の変換用配列
	char c[256];

	// 文字列
	LPSTR str;
	// ワールド行列
	D3DXMATRIXA16 matWorld;
	// 色
	D3DCOLOR color;
	// ブレンドタイプ
	D3DBLEND srcBlend;
	D3DBLEND destBlend;
};

#endif
