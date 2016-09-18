#ifndef BLUEPLANET_H
#define BLUEPLANET_H

#include "Back.h"

//=============================================================
// CBluePlanet
//-------------------------------------------------------------
// 背景用星クラス。
//=============================================================
class CBluePlanet : public CBack, public CThingMesh
{
public:
	CBluePlanet(CTaskList *taskList, CHandleGraphics *hGrap);
	~CBluePlanet();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	int timer;
};

#endif