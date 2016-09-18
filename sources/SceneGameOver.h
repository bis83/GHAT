#ifndef SCENEGAMEOVER_H
#define SCENEGAMEOVER_H

#include "SystemScene.h"
#include "SceneBase.h"

//=============================================================
// CSceneGameOver
//-------------------------------------------------------------
// �Q�[���I�[�o�[�y�уl�[���G���g���[�V�[���B
//=============================================================
class CSceneGameOver : public CSceneBase
{
public:
	CSceneGameOver();
	~CSceneGameOver();

	void Update();
	void Draw();
	void Init(CSystemScene *_system);
	void UnInit();
private:
	// �t�H���gID
	int fontID;

	// ��ID
	int planetID;
	// �Q�[���I�[�o�[�摜ID
	int overID;
	D3DXMATRIXA16 mat;
	D3DCOLOR color;
	D3DFILLMODE fill;

	// �J�[�\����ID
	int cursorID;
	// ���艹ID
	int decideID;
	// �L�����Z����ID
	int cancelID;

	// �I�[�o�[��ID
	int overSeID;
	// �l�[���G���g���[���y
	int entryBgmID;

	// �t�F�[�Y
	int phase;
	// �E�F�C�g
	int wait;
	// �l�[��
	char name[4];
	int score;
	int rank;
	// ���O�̉������ڂ̓��͂��H
	int nameIndex;
	// �����I���C���f�b�N�X
	int index;
	// �����e�[�u��
	char charTable[64+1];
};

#endif