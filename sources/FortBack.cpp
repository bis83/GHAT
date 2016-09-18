#include "FortBack.h"
#include "TaskFactory.h"

CFortBack::CFortBack(CTaskList *taskList, CHandleGraphics *hGrap)
: CBack(taskList)
{
	Set("Data/Texture/yousai.png", hGrap);
	vecScale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vecPos = D3DXVECTOR3(0.0f, 0.0f, 250.0f);
	vecRot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI);
	billBoard = TRUE;

	timer = 0;
	dead = false;
}

CFortBack::~CFortBack()
{
}

bool CFortBack::Update()
{
	timer++;
	a = 128 - 127 * cos(timer*D3DX_PI/360);
	if(timer < 1500)		// 左にブロックが流れる
	{
		if(timer % 90 == 89)
		{
			e_taskFactory.CreateRig(2, D3DXVECTOR3(2.5f, 0.8f, 0.0f), D3DXVECTOR3(-0.01f, 0.0f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(2.5f, 0.0f, 0.0f), D3DXVECTOR3(-0.01f, 0.0f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(2.5f, -0.8f, 0.0f), D3DXVECTOR3(-0.01f, 0.0f, 0.0f));
		}
	} else if(timer < 3000) {		// 上下にブロックが交差する
		if(timer % 150 == 149)
		{
			e_taskFactory.CreateRig(2, D3DXVECTOR3(2.4f, 1.5f, 0.0f), D3DXVECTOR3(0.0f, -0.01f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(1.6f, -1.5f, 0.0f), D3DXVECTOR3(0.0f, 0.01f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(0.8f, 1.5f, 0.0f), D3DXVECTOR3(0.0f, -0.01f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(0.0f, -1.5f, 0.0f), D3DXVECTOR3(0.0f, 0.01f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(-0.8f, 1.5f, 0.0f), D3DXVECTOR3(0.0f, -0.01f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(-1.6f, -1.5f, 0.0f), D3DXVECTOR3(0.0f, 0.01f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(-2.4f, 1.5f, 0.0f), D3DXVECTOR3(0.0f, -0.01f, 0.0f));
		}
	} else if(timer < 4500) {		// 左右からブロックが交差する
		if(timer % 90 == 89)
		{
			e_taskFactory.CreateRig(2, D3DXVECTOR3(2.5f, 0.8f, 0.0f), D3DXVECTOR3(-0.01f, 0.0f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(-2.5f, 0.0f, 0.0f), D3DXVECTOR3(0.01f, 0.0f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(2.5f, -0.8f, 0.0f), D3DXVECTOR3(-0.01f, 0.0f, 0.0f));
		}
	} else if(timer < 6000) {		// サイン状に出現する
		if(timer % 45 == 44)
		{
			e_taskFactory.CreateRig(2, D3DXVECTOR3(2.5f, 0.0f+1.0f*sin(timer*D3DX_PI/360), 0.0f), D3DXVECTOR3(-0.02f, 0.0f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(2.5f, 1.5f+1.0f*sin(timer*D3DX_PI/360), 0.0f), D3DXVECTOR3(-0.02f, 0.0f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(2.5f, -1.5f+1.0f*sin(timer*D3DX_PI/360), 0.0f), D3DXVECTOR3(-0.02f, 0.0f, 0.0f));
		}
	} else if(timer < 7500) {		// 右にブロックが流れる
		if(timer % 90 == 89)
		{
			e_taskFactory.CreateRig(2, D3DXVECTOR3(-2.5f, 0.8f, 0.0f), D3DXVECTOR3(0.01f, 0.0f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(-2.5f, 0.0f, 0.0f), D3DXVECTOR3(0.01f, 0.0f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(-2.5f, -0.8f, 0.0f), D3DXVECTOR3(0.01f, 0.0f, 0.0f));
		}
	} else {						// ボス戦(上下にブロックが流れる)
		if(timer % 150 == 149)
		{
			e_taskFactory.CreateRig(2, D3DXVECTOR3(0.0f, -1.5f, 0.0f), D3DXVECTOR3(0.0f, 0.01f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(-0.8f, 1.5f, 0.0f), D3DXVECTOR3(0.0f, -0.01f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(-1.6f, -1.5f, 0.0f), D3DXVECTOR3(0.0f, 0.01f, 0.0f));
			e_taskFactory.CreateRig(2, D3DXVECTOR3(-2.4f, 1.5f, 0.0f), D3DXVECTOR3(0.0f, -0.01f, 0.0f));
		}
	}
	if(timer % 30 == 29)		// 上下のブロック
	{
		e_taskFactory.CreateRig(2, D3DXVECTOR3(2.5f, 1.4f, 0.0f), D3DXVECTOR3(-0.02f, 0.0f, 0.0f));
		e_taskFactory.CreateRig(2, D3DXVECTOR3(2.5f, -1.4f, 0.0f), D3DXVECTOR3(-0.02f, 0.0f, 0.0f));
	}
	return !dead;
}

void CFortBack::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
