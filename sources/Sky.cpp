#include "Sky.h"
#include "TaskFactory.h"

CSky::CSky(CTaskList *taskList, CHandleGraphics *hGrap)
: CBack(taskList)
{
	Set("Data/Texture/sky.png", hGrap);
	vecScale = D3DXVECTOR3(2.0f, 1.0f, 0.0f);
	vecPos = D3DXVECTOR3(0.0f, 0.0f, 500.0f);
	vecRot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI);
	billBoard = TRUE;

	timer = 0;
	dead = false;

	e_taskFactory.CreateBack(3);
}

CSky::~CSky()
{
}

bool CSky::Update()
{
	timer++;
	if(timer < 255)
	{
		a += 1;
	}
	if(timer > 300 && !(timer%80) && timer < 1080)
	{
		e_taskFactory.CreateBack(5);
	}
	if(timer == 960)
	{
		//e_taskFactory.CreateBack(6);
	}
	if(timer > 1200 && !(timer%80))
	{
		e_taskFactory.CreateBack(7);
	}
	return !dead;
}

void CSky::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
