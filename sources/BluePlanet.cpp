#include "BluePlanet.h"
#include "TaskFactory.h"

CBluePlanet::CBluePlanet(CTaskList *taskList, CHandleGraphics *hGrap)
: CBack(taskList)
{
	Set("Data/Mesh/bluePlanet.x", hGrap);
	vecScale = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	vecPos = D3DXVECTOR3(30.0f, 0.0f, 100.0f);
	dead = false;
	timer = 0;
}


CBluePlanet::~CBluePlanet()
{
}

bool CBluePlanet::Update()
{
	timer++;
	if(timer < 1800)
	{
		vecPos.z -= 0.05f;
		vecPos.x -= 0.015f;
	} else {
		e_taskFactory.CreateBack(4);
		dead = true;
	}
	vecRot.y += 0.01f;
	return !dead;
}

void CBluePlanet::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
