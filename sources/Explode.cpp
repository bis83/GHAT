#include "Explode.h"
#include "Config.h"

CExplode::CExplode(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int type)
: CEffect(taskList)
{
	Set("Data/Texture/explode.png", hGrap);
	seed = timeGetTime();
	vecOriPos = vecPos;
	billBoard = TRUE;
	blendType = 1;
	timer = 0;
	dead = false;
	this->type = type;

	int seID;
	seID = hMedi->GetMediaObjectID("Data/Media/explode.wav");
	hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
	hMedi->PlaySE(seID);
}

CExplode::~CExplode()
{
}

void CExplode::Draw(CHandleGraphics *hGrap)
{
	srand(seed);
	switch(type)
	{
	case 1:
		for(int i=0; i<16; i++)
		{
			// 位置のセット
			vecPos.x = vecOriPos.x + (rand() % 100)*0.006f - 0.3f;
			vecPos.y = vecOriPos.y + (rand() % 100)*0.006f - 0.3f;
			vecPos.z = 0.0f;
			// 拡大縮小のセット
			vecScale.x = vecScale.y = 0.1f + timer * 0.005f;
			// アルファ値のセット
			a = (10 - timer) * 255 / 15;
			// 描画
			DrawThing(hGrap);
		}
		break;
	case 2:
		for(int i=0; i<16; i++)
		{
			// 位置のセット
			vecPos.x = vecOriPos.x + (rand() % 100)*0.01f - 0.5f;
			vecPos.y = vecOriPos.y + (rand() % 100)*0.01f - 0.5f;
			vecPos.z = 0.0f;
			// 拡大縮小のセット
			vecScale.x = vecScale.y = 0.1f + timer * 0.005f;
			// アルファ値のセット
			a = (180 - timer) * 255 / 180;
			// 描画
			DrawThing(hGrap);
		}
		break;
	}
}

bool CExplode::Update()
{
	timer++;
	switch(type)
	{
	case 1:
		if(timer > 10)
		{
			dead = true;
		}
		break;
	case 2:
		if(timer > 180)
		{
			dead = true;
		}
		break;
	}
	return !dead;
}