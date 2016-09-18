#include "Seaface.h"

CSeaface::CSeaface(CTaskList *taskList, CHandleGraphics *hGrap)
: CBack(taskList)
{
	Set("Data/Mesh/seaface.x", hGrap);
	vecScale = D3DXVECTOR3(16.0f, 8.0f, 1.0f);
	vecPos = D3DXVECTOR3(8.0f, -4.0f, 4.0f);
	vecRot = D3DXVECTOR3(-D3DX_PI/4, 0.0f, 0.0f);

	timer = 0;
	dead = false;
}

CSeaface::~CSeaface()
{
}

bool CSeaface::Update()
{
	timer++;
	vecPos.x -= 0.02f;
	if(vecPos.x < -8.0f)
	{
		vecPos.x = 8.0f;
	}
	if(timer < 2000)
	{
		vecPos.y += 0.001f;
	}
	return !dead;
}

void CSeaface::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}