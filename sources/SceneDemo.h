#ifndef SCENEDEMO_H
#define SCENEDEMO_H

#include "SceneBase.h"

//=============================================================
// CSceneDemo
//-------------------------------------------------------------
// �^�C�g����ʈڍs�O�̃f���V�[���B
// �{�^���������ƃV���[�g�J�b�g�ł���B
//=============================================================
class CSceneDemo : public CSceneBase
{
public:
	CSceneDemo();
	~CSceneDemo();

	void Update();
	void Draw();
	void Init(CSystemScene *_system);
	void UnInit();
private:
	// �w�iID
	int starID;

	int fontID;
	char string[256];
	D3DCOLOR color;
	D3DBLEND blend;
	BOOL bill;
	D3DXMATRIXA16 mat, mat2;

	// �p�[�e�B�N���ʒu�z��
	D3DXVECTOR2 vecParticlePos[32];
	// �p�[�e�B�N���g�嗦
	float particleScaling[32];

	int time;
};


#endif