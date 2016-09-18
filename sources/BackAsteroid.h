#ifndef BACKASTEROID_H
#define BACKASTEROID_H

#include "Back.h"

//=============================================================
// CBackAsteroid
//-------------------------------------------------------------
// �w�i��覐ΌQ�N���X�B
// 3�d�X�N���[�����炢�ɂ��Č��h�����悭���Ă���B
//=============================================================
class CBackAsteroid : public CBack, public CThingSprite
{
public:
	CBackAsteroid(CTaskList *taskList, CHandleGraphics *hGrap);
	~CBackAsteroid();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	// �����V�[�h
	DWORD seed;
	D3DXVECTOR3 vecOriPos;
	int timer;
};

#endif