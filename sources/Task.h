
#ifndef TASK_H
#define TASK_H

//�v���g�^�C�v�錾
class CTaskList;
class CTaskIter;
class CSystemTask;

//=============================================================
// CTaskBase
//-------------------------------------------------------------
// �S�Ẵ^�X�N�̊�b�N���X
//=============================================================
class CTaskBase
{
	friend CTaskList;
	friend CTaskIter;
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CTaskBase(CTaskList* _taskList);
	virtual ~CTaskBase();

	void* operator new(size_t t) {}
	void operator delete(void* p) {}
protected:
	// �V����new��delete
	static void* operator_new(size_t t, CTaskList* _taskList);
	static void operator_delete(void* p, CTaskList* _taskList);
private:
	CTaskList* taskList;
	CTaskBase *prevTask, *nextTask;
};

//=============================================================
// CTaskList
//-------------------------------------------------------------
// �����̓��n���^�X�N����܂Ƃ߂ɂ���N���X
//=============================================================
class CTaskList
{
	friend CTaskBase;
	friend CTaskIter;
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CTaskList(int max_task_size, int max_num_task);
	~CTaskList();
	// �^�X�N��
	int GetNumFreeTask();
	int GetNumActiveTask();
	// �S�^�X�N�̏���
	void ClearTask();
private:
	// �A�N�e�B�u�^�X�N�A�t���[�^�X�N
	CTaskBase *activeTask, *freeTask;
	// �^�X�N�̍ő�T�C�Y
	int maxTaskSize;
	// �^�X�N�̍ő吔
	int maxNumTask;
	// �t���[�^�X�N��
	int numFreeTask;
};

//=============================================================
// CTaskIter
//-------------------------------------------------------------
// �^�X�N���X�g�ɔ�������������N���X
//=============================================================
class CTaskIter
{
private:
	CTaskList* taskList;
	CTaskBase* task;
public:
	inline CTaskIter(CTaskList* _taskList)
		: taskList(_taskList), task(_taskList->activeTask)
	{}
	inline bool HasNext()
	{
		return task->nextTask != taskList->activeTask;
	}
	inline CTaskBase* Next()
	{
		return task = task->nextTask;
	}
	inline void Remove()
	{
		task = task->prevTask;
		delete task->nextTask;
	}
};

#endif
