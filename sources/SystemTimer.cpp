#include "SystemTimer.h"

CSystemTimer::CSystemTimer(CGameHolding *_holding, int new_fps)
: CSystemBase(_holding)
{
	// �^�C�}�[�̏�����
	SetFPS(new_fps);
	frame = 0;
	prevFrame = 0;
	nowTime = timeGetTime();
	prevTime = nowTime;
	idealTime = (DWORD)(frame * (100.0F / fps));
	progress = 0;
	// �\���t���O�̏�����
	showFPS = false;
}

CSystemTimer::~CSystemTimer()
{
}

void CSystemTimer::Update()
{
	// ���z���Ԃ܂�Sleep����
	nowTime = timeGetTime();
	progress = nowTime - prevTime;
	idealTime = (DWORD)(frame * (100.0F / fps));
	if(idealTime > progress)
		Sleep(idealTime - progress);

	// 1�b���Ƃ�FPS�����肷��
	if(progress >= 1000)
	{
		prevFrame = frame;
		frame = 0;
		prevTime = nowTime;
	}

	// FPS��\������
	if(showFPS)
	{
	}

	// �t���[���̐i�s
	frame++;
}

int CSystemTimer::GetFPS()
{
	return prevFrame;
}

void CSystemTimer::SetFPS(int new_fps)
{
	fps = new_fps;
	// ���t���[�������Z�b�g����
	frame = 0;
	prevTime = nowTime;
}

void CSystemTimer::SetShowFPS(bool flag)
{
	showFPS = flag;
}
