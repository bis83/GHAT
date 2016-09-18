#include "BackAsteroid.h"

#include "TaskFactory.h"

CBackAsteroid::CBackAsteroid(CTaskList *taskList, CHandleGraphics *hGrap)
: CBack(taskList)
{
	seed = timeGetTime();
	vecOriPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->blendType = 1;
	Set("Data/Texture/star2.png", hGrap);
	a = 196;
	dead = false;
	timer = 0;
}

CBackAsteroid::~CBackAsteroid()
{
}

bool CBackAsteroid::Update()
{
	timer++;
	// êØÇÃà⁄ìÆ
	vecOriPos.x -= 3.0f;
	return !dead;
}

void CBackAsteroid::Draw(CHandleGraphics *hGrap)
{
	srand(seed);
	for(int i=0; i<32; i++)
	{
		vecPos.x = (vecOriPos.x * (1+(i/16)))/4 + rand() % 1280;
		while(vecPos.x < -200)
		{
			vecPos.x += 1600;
			vecPos.y += 10;
			while(vecPos.y > 800)
			{
				vecPos.y -= 720;
			}
		}
		vecPos.y = vecOriPos.y + rand() % 720;
		vecPos.z = 1;
		vecScale.x = vecScale.y = 1.0f + 0.2f * (i/16);
		DrawThing(hGrap);
	}
}
