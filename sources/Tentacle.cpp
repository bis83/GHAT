#include "Tentacle.h"

#include "Config.h"

CTentacle::CTentacle(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos)
: CShot(taskList)
{
	Set("Data/Mesh/tentacle.x", hGrap);
	this->vecPos = vecPos;
	hit.c = vecPos;
	hit.c.x += 0.01f;
	hit.r = 0.1f;
	vecScale = D3DXVECTOR3(0.01f, 0.1f, 0.1f);
	power = 2;
	shotType = 0;
	dead = false;
	timer = 0;

	int seID;
	seID = hMedi->GetMediaObjectID("Data/Media/tentacle.wav");
	hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
	hMedi->PlaySE(seID);
}

CTentacle::~CTentacle()
{
}

bool CTentacle::Update()
{
	timer++;

	vecPos = e_MyShip.vecPos;
	if(timer < 5)
	{
		vecScale.x += 0.04f;
	}
	if(timer > 10)
	{
		vecScale.x -= 0.02f;
	}
	hit.c = vecPos;
	hit.c.x += 3.0f * (vecScale.x - 0.01f);

	return timer < 20;
}

bool CTentacle::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

void CTentacle::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
