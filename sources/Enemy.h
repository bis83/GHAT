#ifndef ENEMY_H
#define ENEMY_H

#include "Task.h"
#include "Thing.h"

#include "Dynamics.h"
#include "HandleSystem.h"

#include "TaskManager.h"
#include "MyShip.h"

//=============================================================
// CEnemy
//-------------------------------------------------------------
// �G�^�X�N�̊��N���X�B
//=============================================================
class CEnemy : public CThingMesh, public CTaskBase
{
public:
	CEnemy(CTaskList *_taskList)
		: CTaskBase(_taskList)
	{
	}
	virtual ~CEnemy()
	{
	}
	// new, delete�̃I�[�o�[���C�h
	void* operator new(size_t t)
	{
		return operator_new(t, e_taskMgr.enemy);
	}
	void operator delete(void* p)
	{
		operator_delete(p, e_taskMgr.enemy);
	}

	// �X�V�A�����蔻��A�`��
	virtual bool Update(CHandleMedia *hMedi) = 0;
	virtual bool Hit(CDynamics *target) = 0;
	virtual void Draw(CHandleGraphics *hGrap) = 0;

	void Dead()
	{
		dead = true;
	}
	void Damage(int d)
	{
		life -= d;
	}
	int GetEnemyID()
	{
		return enemyID;
	}
	bool IsDead()
	{
		return dead || life <= 0;
	}
	// �_�C�i�~�N�X�̎擾
	virtual CDynamics* GetDynamics() = 0;
protected:
	// �G�l�~�[�ԍ�
	int enemyID;
	// �ϋv��
	int life;
	// ���S�t���O
	bool dead;

	// ��ʊO����
	bool OutSurface()
	{
		if(vecPos.x > 3.0f || vecPos.x < -3.0f || vecPos.y > 3.0f || vecPos.y < -3.0f)
		{
			return true;
		}
		return false;
	}
};

#endif