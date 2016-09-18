#include "Smoke.h"

CSmoke::CSmoke(CTaskList *taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos)
: CEffect(taskList)
{
	Set("Data/Texture/smoke.png", hGrap);
	billBoard = TRUE;
	this->vecPos = vecPos;
	vecScale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);
	blendType = 1;
	timer = 0;
}

CSmoke::~CSmoke()
{
}

bool CSmoke::Update()
{
	timer++;
	a = 255 * (20-timer) / 20;
	vecScale.x += 0.005f;
	vecScale.y += 0.005f;
	return timer < 20;
}

void CSmoke::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}