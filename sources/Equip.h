#ifndef EQUIP_H
#define EQUIP_H

#include "Effect.h"

//=============================================================
// CEquip
//-------------------------------------------------------------
// �����擾���̃G�t�F�N�g�B
//=============================================================
class CEquip : public CEffect
{
public:
	CEquip(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos);
	~CEquip();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	// �����Œ�p�V�[�h
	DWORD seed;
	int timer;
};

#endif
