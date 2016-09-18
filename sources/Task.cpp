#include "windows.h"
#include "Task.h"

void* CTaskBase::operator_new(size_t t, CTaskList *_taskList)
{
	if(t > (size_t)_taskList->maxTaskSize)
		return NULL;

	if(_taskList->numFreeTask <= 0)
		return NULL;

	CTaskBase* task = _taskList->freeTask->nextTask;
	_taskList->freeTask->nextTask = task->nextTask;
	_taskList->numFreeTask--;

	return task;
}

CTaskBase::CTaskBase(CTaskList *_taskList)
: taskList(_taskList)
{
	prevTask = taskList->activeTask->prevTask;
	nextTask = taskList->activeTask;
	prevTask->nextTask = nextTask->prevTask = this;
}

CTaskBase::~CTaskBase()
{
	prevTask->nextTask = nextTask;
	nextTask->prevTask = prevTask;
}

void CTaskBase::operator_delete(void *p, CTaskList *_taskList)
{
	CTaskBase* task = (CTaskBase*)p;

	task->nextTask = _taskList->freeTask->nextTask;
	_taskList->freeTask->nextTask = task;
	_taskList->numFreeTask++;
}

#define TASK(INDEX) ((CTaskBase*)(buf+max_task_size*(INDEX)))

CTaskList::CTaskList(int max_task_size, int max_num_task)
: maxTaskSize(max_task_size), maxNumTask(max_num_task), numFreeTask(max_num_task)
{
	char* buf = new char[max_task_size*(max_num_task*2)];

	activeTask = TASK(0);
	activeTask->prevTask = activeTask;
	activeTask->nextTask = activeTask;

	freeTask = TASK(1);
	for(int i= 1; i<max_num_task+1; i++)
	{
		TASK(i)->nextTask = TASK(i+1);
	}
	TASK(max_num_task+1)->nextTask = freeTask;
}

CTaskList::~CTaskList()
{
	ClearTask();
}

int CTaskList::GetNumActiveTask()
{
	return maxNumTask - numFreeTask;
}

int CTaskList::GetNumFreeTask()
{
	return numFreeTask;
}

void CTaskList::ClearTask()
{
	for(CTaskIter i(this); i.HasNext(); i.Next(), i.Remove());
}
