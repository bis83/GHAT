#ifndef EXPLODE_H
#define EXPLODE_H

#include "Effect.h"

//=============================================================
// CExplode
//-------------------------------------------------------------
// �����N���X�B
// �����ɂ���Ĕ����̋K�͂�ς��邱�Ƃ��ł���B
//=============================================================
class CExplode : public CEffect
{
public:
	CExplode(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int type);
	~CExplode();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	// �����Œ�p�V�[�h
	DWORD seed;
	int timer;
	int type;
};

#endif
