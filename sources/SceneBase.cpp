#include "SceneBase.h"

CSceneBase::CSceneBase()
{
}

CSceneBase::~CSceneBase()
{
}

void CSceneBase::Init(CSystemScene* _system)
{
	system = _system;
}

void CSceneBase::UnInit()
{
}

int CSceneBase::GetInput(int playerNumber, int keyNumber)
{
	return system->GetInput()->GetInput(playerNumber, keyNumber);
}

int CSceneBase::GetFPS()
{
	return system->GetTimer()->GetFPS();
}

CHandleGraphics* CSceneBase::GetGraphics()
{
	return system->hGraphics;
}

CHandleMedia* CSceneBase::GetMedia()
{
	return system->hMedia;
}

void CSceneBase::MoveScene(CSceneBase *next)
{
	system->MoveScene(next);
}

void CSceneBase::GameEnd()
{
	system->GameEnd();
}