#ifndef SYSTEMTASK_H
#define SYSTEMTASK_H

#include "GameHolding.h"
#include "Task.h"
#include <map>

using namespace std;

//=============================================================
// CSystemTask
//-------------------------------------------------------------
// �Q�[�������S�ʂ̃^�X�N���Ǘ�����N���X�B
//=============================================================
class CSystemTask : public CSystemBase
{
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CSystemTask(CGameHolding* _holding);
	~CSystemTask();
	// �V�����^�X�N���X�g�̍쐬
	bool CreateTaskList(int task_list_id, int max_task_size, int max_num_task);
	// �^�X�N���X�g�̍폜
	void RemoveTaskList(int task_list_id);
	// �^�X�N���X�g�̑S�폜
	void ClearTaskList();
	// �^�X�N���X�g�̎擾
	CTaskList* GetTaskList(int id);
private:
	// �^�X�N���X�g�̔z��
	std::map<int, CTaskList*> taskMap;
};

#endif
