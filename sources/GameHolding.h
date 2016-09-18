#ifndef GAMEHOLDING_H
#define GAMEHOLDING_H

#include <windows.h>

// 各システムクラスのプロトタイプ宣言
class CSystemInput;
class CSystemGraphics;
class CSystemScene;
class CSystemMedia;
class CSystemTimer;

//=============================================================
// CGameHolding
//-------------------------------------------------------------
// ゲーム全体を包括するクラス。
// ゲームシステムオブジェクトの相互アクセスを可能にする。
//=============================================================
class CGameHolding
{
public:
	// コンストラクタ、デストラクタ
	CGameHolding(HWND hWnd);
	~CGameHolding();
	// 更新
	void Update();
	// リフレッシュ
	void Reflesh();

	// グラフィックスへのアクセス
	CSystemGraphics* GetGraphics();
	// メディアへのアクセス
	CSystemMedia* GetMedia();
	// シーンへのアクセス
	CSystemScene* GetScene();
	// インプットへのアクセス
	CSystemInput* GetInput();
	// タイマーへのアクセス
	CSystemTimer* GetTimer();
	// ゲームの終了
	void GameEnd();
protected:
private:
	// グラフィックス
	CSystemGraphics *graphics;
	// メディア
	CSystemMedia *media;
	// シーン
	CSystemScene *scene;
	// タイマー
	CSystemTimer *timer;
	// インプット
	CSystemInput *input;
	// ゲーム終了フラグ
	bool end_f;
};

//=============================================================
// CSystemBase
//-------------------------------------------------------------
// システムクラスの親クラス。
// ゲームホールディングへのポインタを保持し、
// システム間の相互アクセスをサポートする。
//=============================================================
class CSystemBase
{
public:
	// コンストラクタ、デストラクタ
	CSystemBase(CGameHolding* _holding);
	virtual ~CSystemBase();
protected:
	// グラフィックスへのアクセス
	CSystemGraphics* GetGraphics();
	// メディアへのアクセス
	CSystemMedia* GetMedia();
	// シーンへのアクセス
	CSystemScene* GetScene();
	// インプットへのアクセス
	CSystemInput* GetInput();
	// タイマーへのアクセス
	CSystemTimer* GetTimer();
	// ゲームの終了
	void GameEnd();
private:
	CGameHolding *holding;
};

#endif
