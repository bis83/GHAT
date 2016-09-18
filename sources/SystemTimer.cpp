#include "SystemTimer.h"

CSystemTimer::CSystemTimer(CGameHolding *_holding, int new_fps)
: CSystemBase(_holding)
{
	// タイマーの初期化
	SetFPS(new_fps);
	frame = 0;
	prevFrame = 0;
	nowTime = timeGetTime();
	prevTime = nowTime;
	idealTime = (DWORD)(frame * (100.0F / fps));
	progress = 0;
	// 表示フラグの初期化
	showFPS = false;
}

CSystemTimer::~CSystemTimer()
{
}

void CSystemTimer::Update()
{
	// 理想時間までSleepする
	nowTime = timeGetTime();
	progress = nowTime - prevTime;
	idealTime = (DWORD)(frame * (100.0F / fps));
	if(idealTime > progress)
		Sleep(idealTime - progress);

	// 1秒ごとにFPSを決定する
	if(progress >= 1000)
	{
		prevFrame = frame;
		frame = 0;
		prevTime = nowTime;
	}

	// FPSを表示する
	if(showFPS)
	{
	}

	// フレームの進行
	frame++;
}

int CSystemTimer::GetFPS()
{
	return prevFrame;
}

void CSystemTimer::SetFPS(int new_fps)
{
	fps = new_fps;
	// 現フレームをリセットする
	frame = 0;
	prevTime = nowTime;
}

void CSystemTimer::SetShowFPS(bool flag)
{
	showFPS = flag;
}
