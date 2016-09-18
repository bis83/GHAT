#include "SystemScene.h"
#include "SceneBase.h"

CSystemScene::CSystemScene(CGameHolding* _holding)
: CSystemBase(_holding)
{
	scene = NULL;
	nextScene = NULL;
	hGraphics = new CHandleGraphics(GetGraphics());
	hMedia = new CHandleMedia(GetMedia());
}

CSystemScene::~CSystemScene()
{
	delete scene;
	delete hGraphics;
	delete hMedia;
}

void CSystemScene::Update()
{
	if(nextScene != NULL)
	{
		// 新しいシーンの初期化
		nextScene->Init(this);
		// 古いシーンの解放
		if(scene != NULL)
		{
			scene->UnInit();
		}
		delete scene;
		// 新しいシーンへの移行
		scene = nextScene;
		nextScene = NULL;
	}
	// シーンが存在する場合は更新
	if(scene != NULL)
	{
		scene->Update();
	} else {
		GameEnd();
	}
}

void CSystemScene::Draw()
{
	if(scene == NULL)
	{
		return;
	}
	if(!GetGraphics()->Drawing())
	{
		return;
	}
	scene->Draw();
}

void CSystemScene::MoveScene(CSceneBase *next)
{
	nextScene = next;
}
