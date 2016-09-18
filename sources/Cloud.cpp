#include "Cloud.h"

CCloud::CCloud(CTaskList *taskList, CHandleGraphics *hGrap, int type)
: CBack(taskList)
{
	switch(type)
	{
	case 1:
		vecOriPos = D3DXVECTOR3(1.0f, -2.3f, 0.0f);
		break;
	case 2:
		vecOriPos = D3DXVECTOR3(5.0f, fabs(cos((float)rand()))*1.0f+0.6f, 0.0f);
		break;
	}
	seed = timeGetTime();
	vecScale = D3DXVECTOR3(0.08f, 0.04f, 0.0f);
	this->blendType = 1;
	a = 32;
	Set("Data/Texture/cloud_cell.png", hGrap);
	billBoard = TRUE;
	dead = false;
	timer = 0;
	this->type = type;
}

CCloud::~CCloud()
{
}

bool CCloud::Update()
{
	timer++;
	switch(type)
	{
	case 1:
		vecOriPos.y += 0.02f;
		vecOriPos.x -= 0.01f;
		break;
	case 2:
		vecOriPos.x -= 0.03f;
		break;
	}
	if(vecOriPos.y > 2.3f)
	{
		dead = true;
	}
	if(vecOriPos.x < -5.0f)
	{
		dead = true;
	}
	return !dead;
}

void CCloud::Draw(CHandleGraphics *hGrap)
{
	srand(seed);
	for(int i=0; i<48; i++)
	{
		// 位置のセット
		vecPos.x = vecOriPos.x + (rand() % 100)*0.04f - 2.0f;
		vecPos.y = vecOriPos.y + (rand() % 100)*0.02f - 1.0f;
		vecPos.z = vecOriPos.z;
		// 描画
		DrawThing(hGrap);
	}
}
