#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H

#include <windows.h>

#include "GameHolding.h"

#pragma comment(lib, "winmm.lib")

//=============================================================
// CSystemTimer
//-------------------------------------------------------------
// FPS���v������V�X�e���N���X
//=============================================================
class CSystemTimer : public CSystemBase
{
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CSystemTimer(CGameHolding* _holding, int new_fps);
	~CSystemTimer();

	// �X�V
	void Update();
	// FPS�̎擾
	int GetFPS();
	// FPS�̐ݒ�
	void SetFPS(int new_fps);
	// FPS�\���̐؂�ւ�
	void SetShowFPS(bool flag);
protected:
private:
	// FPS
	int fps;
	// ���݂̃t���[���A�O�t���[��
	int frame, prevFrame;
	// ���ݎ��ԁA�O�t���[���̎��ԁA���z���ԁA�o�ߎ���
	DWORD nowTime, prevTime, idealTime, progress;
	// FPS�̕\���t���O
	bool showFPS;
};

#endif
