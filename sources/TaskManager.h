#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include "Boss.h"

//=============================================================
// CTaskManager
//-------------------------------------------------------------
// 全てのタスクを管理するクラス。
// グローバルなインスタンスとして扱う。
//=============================================================
class CTaskManager
{
public:
	CTaskManager();
	~CTaskManager();

	// 初期化
	void Init();
	// 解放
	void UnInit();

	// 背景タスク
	CTaskList* back;
	// アイテムタスク
	CTaskList* item;
	// ショットタスク
	CTaskList* shot;
	// エネミータスク
	CTaskList* enemy;
	// エネミーバレットタスク
	CTaskList* bullet;
	// 地形タスク
	CTaskList* rig;
	// エフェクトタスク
	CTaskList* effect;
	// ボス
	CBoss *boss;
};

extern CTaskManager e_taskMgr;

#endif