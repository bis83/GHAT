#include "Equip.h"

#include "Config.h"

CEquip::CEquip(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos)
: CEffect(taskList)
{
	Set("Data/Texture/equip.png", hGrap);
	billBoard = TRUE;
	this->vecPos = vecPos;
	vecScale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);
	blendType = 1;
	timer = 0;

	int seID;
	seID = hMedi->GetMediaObjectID("Data/Media/powerup.wav");
	hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
	hMedi->PlaySE(seID);
}

CEquip::~CEquip()
{
}

bool CEquip::Update()
{
	timer++;
	vecRot.z += 0.01f;
	vecScale.x += 0.005f;
	vecScale.y += 0.005f;
	a -= 10;
	return timer < 20;
}

void CEquip::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}

