#ifndef BACKSTAR_H
#define BACKSTAR_H

#include "Back.h"

//=============================================================
// CBackStar
//-------------------------------------------------------------
// �w�i�̐��N���X�B
// 3�d�X�N���[�����炢�ɂ��Č��h�����悭���Ă���B
//=============================================================
class CBackStar : public CBack, public CThingSprite
{
public:
	CBackStar(CTaskList *taskList, CHandleGraphics *hGrap);
	~CBackStar();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	// �����V�[�h
	DWORD seed;
	D3DXVECTOR3 vecOriPos;
	int timer;
};

#endif