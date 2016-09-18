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
		// �V�����V�[���̏�����
		nextScene->Init(this);
		// �Â��V�[���̉��
		if(scene != NULL)
		{
			scene->UnInit();
		}
		delete scene;
		// �V�����V�[���ւ̈ڍs
		scene = nextScene;
		nextScene = NULL;
	}
	// �V�[�������݂���ꍇ�͍X�V
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
