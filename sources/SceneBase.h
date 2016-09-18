#ifndef SCENEBASE_H
#define SCENEBASE_H

#include "SystemScene.h"
#include "SystemGraphics.h"
#include "SystemMedia.h"
#include "SystemInput.h"
#include "SystemTimer.h"

#include "HandleSystem.h"

//=============================================================
// CSceneBase
//-------------------------------------------------------------
// 全てのシーンの基底クラス。
// protected継承ですべての必要なメンバ関数を引き継ぐ。
//=============================================================
class CSceneBase
{
public:
	// コンストラクタ、デストラクタ
	CSceneBase();
	~CSceneBase();
	// 更新
	virtual void Update() = 0;
	// 描画(グラフィックスから呼び出される)
	virtual void Draw() = 0;
	// 初期化(シーンの開始時に呼び出される)
	virtual void Init(CSystemScene* _system);
	// 解放(シーンの終了時に呼び出される)
	virtual void UnInit();
protected:
	// インプット情報の取得
	int GetInput(int playerNumber, int keyNumber);
	// タイマー情報の取得
	int GetFPS();
	// グラフィックスへのアクセス
	CHandleGraphics* GetGraphics();
	// メディアへのアクセス
	CHandleMedia* GetMedia();
	// シーンの移行
	void MoveScene(CSceneBase* next);
	// ゲームの終了
	void GameEnd();
private:
	// システムへのポインタ
	CSystemScene* system;
};

#endif
