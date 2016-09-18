#ifndef SMOKE_H
#define SMOKE_H

#include "Effect.h"

//=============================================================
// CSmoke
//-------------------------------------------------------------
// �~�T�C���̉��G�t�F�N�g�B
//==============================================================
class CSmoke : public CEffect
{
public:
	CSmoke(CTaskList *taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos);
	~CSmoke();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	int timer;
};

#endif
