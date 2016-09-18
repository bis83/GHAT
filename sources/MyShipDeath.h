#ifndef MYSHIPDEATH_H
#define MYSHIPDEATH_H

#include "Effect.h"

//=============================================================
// CMyShipDeath
//-------------------------------------------------------------
// ���@�̎��S���̔����G�t�F�N�g�B
//=============================================================
class CMyShipDeath : public CEffect
{
public:
	CMyShipDeath(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos);
	~CMyShipDeath();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	// �����Œ�p�V�[�h
	DWORD seed;
	int timer;
};

#endif
