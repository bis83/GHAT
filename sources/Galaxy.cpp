#include "Galaxy.h"
#include "TaskFactory.h"

CGalaxy::CGalaxy(CTaskList *taskList, CHandleGraphics *hGrap)
: CBack(taskList)
{
	Set("Data/Texture/galaxy.png", hGrap);
	vecScale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vecPos = D3DXVECTOR3(0.0f, 0.0f, 250.0f);
	vecRot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI);
	billBoard = TRUE;

	timer = 0;
	dead = false;

	e_taskFactory.CreateBack(1);
}

CGalaxy::~CGalaxy()
{
}

bool CGalaxy::Update()
{
	timer++;
	if(timer > 1800)
	{
		dead = true;
	}
	return !dead;
}

void CGalaxy::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
