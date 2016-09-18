#include "MyShipDeath.h"
#include "Config.h"

CMyShipDeath::CMyShipDeath(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos)
: CEffect(taskList)
{
	Set("Data/Texture/explode2.png", hGrap);
	seed = timeGetTime();
	vecOriPos = vecPos;
	billBoard = TRUE;
	blendType = 1;
	timer = 0;
	dead = false;

	int seID;
	seID = hMedi->GetMediaObjectID("Data/Media/explode.wav");
	hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
	hMedi->PlaySE(seID);
}

CMyShipDeath::~CMyShipDeath()
{
}

void CMyShipDeath::Draw(CHandleGraphics *hGrap)
{
	srand(seed);
	for(int i=0; i<32; i++)
	{
		// �ʒu�̃Z�b�g
		vecPos.x = vecOriPos.x + (rand() % 100)*0.006f - 0.3f;
		vecPos.y = vecOriPos.y + (rand() % 100)*0.006f - 0.3f;
		vecPos.z = 0.0f;
		// �g��k���̃Z�b�g
		vecScale.x = vecScale.y = 0.1f + timer * 0.005f;
		// �A���t�@�l�̃Z�b�g
		a = (10 - timer) * 255 / 15;
		// �`��
		DrawThing(hGrap);
	}
}

bool CMyShipDeath::Update()
{
	timer++;
	if(timer > 10)
	{
		dead = true;
	}
	return !dead;
}
