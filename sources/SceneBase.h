#ifndef SCENEBASE_H
#define SCENEBASE_H

#include "SystemScene.h"
#include "SystemGraphics.h"
#include "SystemMedia.h"
#include "SystemInput.h"
#include "SystemTimer.h"

#include "HandleSystem.h"

//=============================================================
// CSceneBase
//-------------------------------------------------------------
// �S�ẴV�[���̊��N���X�B
// protected�p���ł��ׂĂ̕K�v�ȃ����o�֐��������p���B
//=============================================================
class CSceneBase
{
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CSceneBase();
	~CSceneBase();
	// �X�V
	virtual void Update() = 0;
	// �`��(�O���t�B�b�N�X����Ăяo�����)
	virtual void Draw() = 0;
	// ������(�V�[���̊J�n���ɌĂяo�����)
	virtual void Init(CSystemScene* _system);
	// ���(�V�[���̏I�����ɌĂяo�����)
	virtual void UnInit();
protected:
	// �C���v�b�g���̎擾
	int GetInput(int playerNumber, int keyNumber);
	// �^�C�}�[���̎擾
	int GetFPS();
	// �O���t�B�b�N�X�ւ̃A�N�Z�X
	CHandleGraphics* GetGraphics();
	// ���f�B�A�ւ̃A�N�Z�X
	CHandleMedia* GetMedia();
	// �V�[���̈ڍs
	void MoveScene(CSceneBase* next);
	// �Q�[���̏I��
	void GameEnd();
private:
	// �V�X�e���ւ̃|�C���^
	CSystemScene* system;
};

#endif
