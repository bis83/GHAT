
#ifndef TASK_H
#define TASK_H

//プロトタイプ宣言
class CTaskList;
class CTaskIter;
class CSystemTask;

//=============================================================
// CTaskBase
//-------------------------------------------------------------
// 全てのタスクの基礎クラス
//=============================================================
class CTaskBase
{
	friend CTaskList;
	friend CTaskIter;
public:
	// コンストラクタ、デストラクタ
	CTaskBase(CTaskList* _taskList);
	virtual ~CTaskBase();

	void* operator new(size_t t) {}
	void operator delete(void* p) {}
protected:
	// 新しいnewとdelete
	static void* operator_new(size_t t, CTaskList* _taskList);
	static void operator_delete(void* p, CTaskList* _taskList);
private:
	CTaskList* taskList;
	CTaskBase *prevTask, *nextTask;
};

//=============================================================
// CTaskList
//-------------------------------------------------------------
// 複数の同系統タスクを一まとめにするクラス
//=============================================================
class CTaskList
{
	friend CTaskBase;
	friend CTaskIter;
public:
	// コンストラクタ、デストラクタ
	CTaskList(int max_task_size, int max_num_task);
	~CTaskList();
	// タスク数
	int GetNumFreeTask();
	int GetNumActiveTask();
	// 全タスクの消去
	void ClearTask();
private:
	// アクティブタスク、フリータスク
	CTaskBase *activeTask, *freeTask;
	// タスクの最大サイズ
	int maxTaskSize;
	// タスクの最大数
	int maxNumTask;
	// フリータスク数
	int numFreeTask;
};

//=============================================================
// CTaskIter
//-------------------------------------------------------------
// タスクリストに反復処理させるクラス
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
