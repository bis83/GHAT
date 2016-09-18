#include "SystemTask.h"

CSystemTask::CSystemTask(CGameHolding* _holding)
: CSystemBase(_holding)
{
}

CSystemTask::~CSystemTask()
{
}

bool CSystemTask::CreateTaskList(int task_list_id, int max_task_size, int max_num_task)
{
	if(taskMap[task_list_id] != NULL)
	{
		return false;
	}

	taskMap[task_list_id] = new CTaskList(this, max_task_size, max_num_task);

	if(taskMap[task_list_id] != NULL)
	{
		return true;
	}

	return false;
}

void CSystemTask::RemoveTaskList(int task_list_id)
{
	if(taskMap[task_list_id] != NULL)
	{
		taskMap[task_list_id]->ClearTask();
	}
	taskMap.erase(task_list_id);
}

void CSystemTask::ClearTaskList()
{
	taskMap.clear();
}

CTaskList* CSystemTask::GetTaskList(int id)
{
	if(taskMap[id] != NULL)
	{
		return taskMap[id];
	} else {
		return NULL;
	}
}
