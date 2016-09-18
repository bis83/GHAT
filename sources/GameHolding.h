#ifndef GAMEHOLDING_H
#define GAMEHOLDING_H

#include <windows.h>

// �e�V�X�e���N���X�̃v���g�^�C�v�錾
class CSystemInput;
class CSystemGraphics;
class CSystemScene;
class CSystemMedia;
class CSystemTimer;

//=============================================================
// CGameHolding
//-------------------------------------------------------------
// �Q�[���S�̂�����N���X�B
// �Q�[���V�X�e���I�u�W�F�N�g�̑��݃A�N�Z�X���\�ɂ���B
//=============================================================
class CGameHolding
{
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CGameHolding(HWND hWnd);
	~CGameHolding();
	// �X�V
	void Update();
	// ���t���b�V��
	void Reflesh();

	// �O���t�B�b�N�X�ւ̃A�N�Z�X
	CSystemGraphics* GetGraphics();
	// ���f�B�A�ւ̃A�N�Z�X
	CSystemMedia* GetMedia();
	// �V�[���ւ̃A�N�Z�X
	CSystemScene* GetScene();
	// �C���v�b�g�ւ̃A�N�Z�X
	CSystemInput* GetInput();
	// �^�C�}�[�ւ̃A�N�Z�X
	CSystemTimer* GetTimer();
	// �Q�[���̏I��
	void GameEnd();
protected:
private:
	// �O���t�B�b�N�X
	CSystemGraphics *graphics;
	// ���f�B�A
	CSystemMedia *media;
	// �V�[��
	CSystemScene *scene;
	// �^�C�}�[
	CSystemTimer *timer;
	// �C���v�b�g
	CSystemInput *input;
	// �Q�[���I���t���O
	bool end_f;
};

//=============================================================
// CSystemBase
//-------------------------------------------------------------
// �V�X�e���N���X�̐e�N���X�B
// �Q�[���z�[���f�B���O�ւ̃|�C���^��ێ����A
// �V�X�e���Ԃ̑��݃A�N�Z�X���T�|�[�g����B
//=============================================================
class CSystemBase
{
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CSystemBase(CGameHolding* _holding);
	virtual ~CSystemBase();
protected:
	// �O���t�B�b�N�X�ւ̃A�N�Z�X
	CSystemGraphics* GetGraphics();
	// ���f�B�A�ւ̃A�N�Z�X
	CSystemMedia* GetMedia();
	// �V�[���ւ̃A�N�Z�X
	CSystemScene* GetScene();
	// �C���v�b�g�ւ̃A�N�Z�X
	CSystemInput* GetInput();
	// �^�C�}�[�ւ̃A�N�Z�X
	CSystemTimer* GetTimer();
	// �Q�[���̏I��
	void GameEnd();
private:
	CGameHolding *holding;
};

#endif
