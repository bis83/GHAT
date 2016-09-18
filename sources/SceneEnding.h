#ifndef SCENEENDING_H
#define SCENEENDING_H

#include "SceneBase.h"

//=============================================================
// CSceneEnding
//-------------------------------------------------------------
// �G���f�B���O�f���V�[���B
// �{�^���������ƃV���[�g�J�b�g�ł���B
//=============================================================
class CSceneEnding : public CSceneBase
{
public:
	CSceneEnding();
	~CSceneEnding();

	void Update();
	void Draw();
	void Init(CSystemScene *_system);
	void UnInit();
private:

	int fontID;
	char string[256];
	D3DCOLOR color;
	D3DBLEND blend;
	D3DXMATRIXA16 mat;

	int time;
};

#endif