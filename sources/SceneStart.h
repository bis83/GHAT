#ifndef SCENESTART_H
#define SCENESTART_H

#include "SystemScene.h"
#include "SceneBase.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//=============================================================
// CSceneStart
//-------------------------------------------------------------
// �X�^�[�g�V�[���B
// �Ƃ������t�@�C���̓ǂݍ��ݗp�B
//=============================================================
class CSceneStart : public CSceneBase
{
public:
	CSceneStart();
	~CSceneStart();

	void Update();
	void Draw();
	void Init(CSystemScene *_system);
	void UnInit();
private:
	vector<char*> file;
	int index;

	// �v���[�Y�E�F�C�gID
	int waitID;
	// �E�F�C�g
	int wait;
};

#endif
