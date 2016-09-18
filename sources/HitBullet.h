#ifndef HITBULLET_H
#define HITBULLET_H

#include "Effect.h"

//=============================================================
// CHitBullet
//-------------------------------------------------------------
// �G�ւ̒e�̃q�b�g���̃G�t�F�N�g�N���X�B
//=============================================================
class CHitBullet : public CEffect
{
public:
	CHitBullet(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos);
	~CHitBullet();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	// �����Œ�p�V�[�h
	DWORD seed;
	int timer;
};

#endif
