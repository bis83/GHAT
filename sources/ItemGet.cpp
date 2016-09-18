#include "ItemGet.h"

#include "Config.h"

CItemGet::CItemGet(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos)
: CEffect(taskList)
{
	Set("Data/Texture/itemGet.png", hGrap);
	seed = timeGetTime();
	vecOriPos = vecPos;
	billBoard = TRUE;
	blendType = 1;
	timer = 0;
	dead = false;

	int seID;
	seID = hMedi->GetMediaObjectID("Data/Media/item.wav");
	hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
	hMedi->PlaySE(seID);
}

CItemGet::~CItemGet()
{
}

void CItemGet::Draw(CHandleGraphics *hGrap)
{
	srand(seed);
	for(int i=0; i<4; i++)
	{
		// 位置のセット
		vecPos.x = vecOriPos.x + (rand() % 100)*0.0006f - 0.03f;
		vecPos.y = vecOriPos.y + (rand() % 100)*0.0006f - 0.03f;
		vecPos.z = 0.0f;
		// 拡大縮小のセット
		vecScale.x = vecScale.y = 0.08f + timer * 0.004f;
		// アルファ値のセット
		a = (10 - timer) * 255 / 15;
		// 描画
		DrawThing(hGrap);
	}
}

bool CItemGet::Update()
{
	timer++;
	if(timer > 10)
	{
		dead = true;
	}
	return !dead;
}