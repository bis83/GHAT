#include "DirShot.h"
#include "Config.h"

CDirShot::CDirShot(CTaskList *_taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel)
: CShot(_taskList)
{
	Set("Data/Mesh/tama01.x", hGrap);
	this->vecPos = vecPos;
	this->vecVel = vecVel;
	vecRot = D3DXVECTOR3(0.0f, 0.0f, atan2(vecVel.y, vecVel.x));
	vecScale = D3DXVECTOR3(0.04f, 0.02f, 0.04f);
	hit.c = vecPos;
	hit.r = 0.015f;
	power = 1;
	shotType = 1;
	dead = false;

	int seID;
	seID = hMedi->GetMediaObjectID("Data/Media/shot.wav");
	hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
	hMedi->PlaySE(seID);
}

CDirShot::~CDirShot()
{
}

void CDirShot::Draw(CHandleGraphics *hGrap) {
	DrawThing(hGrap);
}

bool CDirShot::Hit(CDynamics *target) {
	return hit.Hit(target);
}

bool CDirShot::Update() {
	vecPos += vecVel;
	hit.c = vecPos;
	if(OutSurface())
	{
		dead = true;
	}
	return !dead;
}
