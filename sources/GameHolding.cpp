#include "GameHolding.h"
#include "SystemGraphics.h"
#include "SystemInput.h"
#include "SystemScene.h"
#include "SystemTimer.h"
#include "SystemMedia.h"
#include "SystemTask.h"

#include "SafeRelease.h"

CGameHolding::CGameHolding(HWND hWnd)
{
	end_f = false;
	graphics = new CSystemGraphics(this, hWnd);
	media = new CSystemMedia(this, hWnd);
	input = new CSystemInput(this, hWnd);
	timer = new CSystemTimer(this, 60);
	scene = new CSystemScene(this);
}

CGameHolding::~CGameHolding()
{
	SAFE_DELETE(graphics);
	SAFE_DELETE(media);
	SAFE_DELETE(scene);
	SAFE_DELETE(input);
	SAFE_DELETE(timer);
}

void CGameHolding::Update()
{
	// �Q�[���I���t���O
	if(end_f)
	{
		PostQuitMessage(0);
		return;
	}

	// �^�C�}�[�̍X�V
	timer->Update();

	// �C���v�b�g�̍X�V
	input->Update();

	// �V�[���̍X�V
	scene->Update();

	// �`��
	graphics->Draw();

	// �Đ�
	media->Update();
}

void CGameHolding::Reflesh()
{
	// �e�V�X�e���̃��t���b�V��
	input->Reflesh();
}

CSystemGraphics* CGameHolding::GetGraphics()
{
	return graphics;
}

CSystemMedia* CGameHolding::GetMedia()
{
	return media;
}

CSystemScene* CGameHolding::GetScene()
{
	return scene;
}

CSystemInput* CGameHolding::GetInput()
{
	return input;
}

CSystemTimer* CGameHolding::GetTimer()
{
	return timer;
}

void CGameHolding::GameEnd()
{
	end_f = true;
}



CSystemBase::CSystemBase(CGameHolding* _holding)
{
	holding = _holding;
}

CSystemBase::~CSystemBase()
{
}

CSystemGraphics* CSystemBase::GetGraphics()
{
	return holding->GetGraphics();
}

CSystemMedia* CSystemBase::GetMedia()
{
	return holding->GetMedia();
}

CSystemScene* CSystemBase::GetScene()
{
	return holding->GetScene();
}

CSystemInput* CSystemBase::GetInput()
{
	return holding->GetInput();
}

CSystemTimer* CSystemBase::GetTimer()
{
	return holding->GetTimer();
}

void CSystemBase::GameEnd()
{
	holding->GameEnd();
}
