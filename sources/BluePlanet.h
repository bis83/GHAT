#ifndef BLUEPLANET_H
#define BLUEPLANET_H

#include "Back.h"

//=============================================================
// CBluePlanet
//-------------------------------------------------------------
// �w�i�p���N���X�B
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