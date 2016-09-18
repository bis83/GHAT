#ifndef CLOUD_H
#define CLOUD_H

#include "Back.h"
#include "Thing.h"

//=============================================================
// CCloud
//-------------------------------------------------------------
// â_ÉNÉâÉXÅB
//=============================================================
class CCloud : public CBack, public CThingSprite
{
public:
	CCloud(CTaskList *taskList, CHandleGraphics *hGrapm, int type);
	~CCloud();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	DWORD seed;
	int timer;
	int type;
};

#endif
