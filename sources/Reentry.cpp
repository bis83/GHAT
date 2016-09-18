#include "Reentry.h"

#include "TaskFactory.h"

CReentry::CReentry(CTaskList *taskList, CHandleGraphics *hGrap)
: CBack(taskList)
{
	Set("Data/Texture/explode.png", hGrap);
	billBoard = TRUE;
	blendType = 0;

	timer = 0;
	seed = 3;
	dead = false;
}

CReentry::~CReentry()
{
}

void CReentry::Draw(CHandleGraphics *hGrap)
{
	srand(seed);
	for(int i=0; i<32; i++)
	{
		// 位置のセット
		vecPos.x = (rand() % 100)*0.40f - 2.0f;
		vecPos.y = (rand() % 100)*0.20f - 1.0f;
		vecPos.z = 0.0f;
		// 拡大縮小のセット
		vecScale.x = vecScale.y = 0.50f + timer * 0.002f;
		// アルファ値のセット
		a = 255 * (360 - timer) / 360;
		// 描画
		DrawThing(hGrap);
	}
}

bool CReentry::Update()
{
	timer++;
	if(timer > 360)
	{
		dead = true;
	}
	return !dead;
}