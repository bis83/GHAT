#ifndef SCENEMAIN_H
#define SCENEMAIN_H

#include "SceneBase.h"
#include "StageScript.h"

//=============================================================
// CSceneMain
//-------------------------------------------------------------
// �Q�[���̃��C���V�[���B
//=============================================================
class CSceneMain : public CSceneBase
{
public:
	CSceneMain();
	~CSceneMain();

	void Update();
	void Draw();
	void Init(CSystemScene* _system);
	void UnInit();
private:
	// �t�H���gID
	int fontID;
	// ������
	char string[32];
	// �s��
	D3DXMATRIXA16 mat;

	// �A�C�e���擾��
	int itemGetID;

	// �|�[�Y�t���O
	bool pause_f;

	int wait;
	bool gameover;

	// �X�e�[�W�X�N���v�g
	CStageScript script;
};

#endif