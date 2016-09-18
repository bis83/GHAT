#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include "Boss.h"

//=============================================================
// CTaskManager
//-------------------------------------------------------------
// �S�Ẵ^�X�N���Ǘ�����N���X�B
// �O���[�o���ȃC���X�^���X�Ƃ��Ĉ����B
//=============================================================
class CTaskManager
{
public:
	CTaskManager();
	~CTaskManager();

	// ������
	void Init();
	// ���
	void UnInit();

	// �w�i�^�X�N
	CTaskList* back;
	// �A�C�e���^�X�N
	CTaskList* item;
	// �V���b�g�^�X�N
	CTaskList* shot;
	// �G�l�~�[�^�X�N
	CTaskList* enemy;
	// �G�l�~�[�o���b�g�^�X�N
	CTaskList* bullet;
	// �n�`�^�X�N
	CTaskList* rig;
	// �G�t�F�N�g�^�X�N
	CTaskList* effect;
	// �{�X
	CBoss *boss;
};

extern CTaskManager e_taskMgr;

#endif