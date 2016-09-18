#ifndef SYSTEMSCENE_H
#define SYSTEMSCENE_H

#include "GameHolding.h"

#include "HandleSystem.h"

class CSceneBase;

//=============================================================
// CSystemScene
//-------------------------------------------------------------
// �V�[���̏������s���N���X�B
//=============================================================
class CSystemScene : public CSystemBase
{
	friend CSceneBase;
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CSystemScene(CGameHolding* _holding);
	~CSystemScene();
	// �X�V
	void Update();
	// �V�[���̈ڍs
	void MoveScene(CSceneBase *next);
	// �`��
	void Draw();
private:
	// ���݂̃V�[��
	CSceneBase *scene;
	// ���̃V�[��
	CSceneBase *nextScene;
	// �O���t�B�b�N�X�ւ̃n���h��
	CHandleGraphics *hGraphics;
	// ���f�B�A�ւ̃n���h��
	CHandleMedia *hMedia;
};

#endif
