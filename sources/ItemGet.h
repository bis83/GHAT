#ifndef ITEMGET_H
#define ITEMGET_H

#include "Effect.h"

//=============================================================
// CItemGet
//-------------------------------------------------------------
// �A�C�e���擾���̃G�t�F�N�g�N���X�B
//=============================================================
class CItemGet : public CEffect
{
public:
	CItemGet(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos);
	~CItemGet();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	// �����Œ�p�V�[�h
	DWORD seed;
	int timer;
};

#endif
