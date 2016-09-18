#include "HitBullet.h"

#include "Config.h"

CHitBullet::CHitBullet(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos)
: CEffect(taskList)
{
	Set("Data/Texture/hit.png", hGrap);
	seed = timeGetTime();
	vecOriPos = vecPos;
	billBoard = TRUE;
	blendType = 1;
	timer = 0;
	dead = false;

	int seID;
	seID = hMedi->GetMediaObjectID("Data/Media/hit.wav");
	hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
	hMedi->PlaySE(seID);
}

CHitBullet::~CHitBullet()
{
}

void CHitBullet::Draw(CHandleGraphics *hGrap)
{
	srand(seed);
	for(int i=0; i<8; i++)
	{
		// 位置のセット
		vecPos.x = vecOriPos.x + (rand() % 100)*0.002f - 0.1f;
		vecPos.y = vecOriPos.y + (rand() % 100)*0.002f - 0.1f;
		vecPos.z = 0.0f;
		// 拡大縮小のセット
		vecScale.x = vecScale.y = 0.04f + timer * 0.002f;
		// アルファ値のセット
		a = (10 - timer) * 255 / 15;
		// 描画
		DrawThing(hGrap);
	}
}

bool CHitBullet::Update()
{
	timer++;
	if(timer > 10)
	{
		dead = true;
	}
	return !dead;
}