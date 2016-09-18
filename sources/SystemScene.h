#ifndef SYSTEMSCENE_H
#define SYSTEMSCENE_H

#include "GameHolding.h"

#include "HandleSystem.h"

class CSceneBase;

//=============================================================
// CSystemScene
//-------------------------------------------------------------
// シーンの処理を行うクラス。
//=============================================================
class CSystemScene : public CSystemBase
{
	friend CSceneBase;
public:
	// コンストラクタ、デストラクタ
	CSystemScene(CGameHolding* _holding);
	~CSystemScene();
	// 更新
	void Update();
	// シーンの移行
	void MoveScene(CSceneBase *next);
	// 描画
	void Draw();
private:
	// 現在のシーン
	CSceneBase *scene;
	// 次のシーン
	CSceneBase *nextScene;
	// グラフィックスへのハンドル
	CHandleGraphics *hGraphics;
	// メディアへのハンドル
	CHandleMedia *hMedia;
};

#endif
