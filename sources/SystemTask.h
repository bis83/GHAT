#ifndef SYSTEMTASK_H
#define SYSTEMTASK_H

#include "GameHolding.h"
#include "Task.h"
#include <map>

using namespace std;

//=============================================================
// CSystemTask
//-------------------------------------------------------------
// ゲーム処理全般のタスクを管理するクラス。
//=============================================================
class CSystemTask : public CSystemBase
{
public:
	// コンストラクタ、デストラクタ
	CSystemTask(CGameHolding* _holding);
	~CSystemTask();
	// 新しいタスクリストの作成
	bool CreateTaskList(int task_list_id, int max_task_size, int max_num_task);
	// タスクリストの削除
	void RemoveTaskList(int task_list_id);
	// タスクリストの全削除
	void ClearTaskList();
	// タスクリストの取得
	CTaskList* GetTaskList(int id);
private:
	// タスクリストの配列
	std::map<int, CTaskList*> taskMap;
};

#endif
