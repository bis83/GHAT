#ifndef SCENETITLE_H
#define SCENETITLE_H

#include "SceneBase.h"

//=============================================================
// CSceneTitle
//-------------------------------------------------------------
// �^�C�g���y�уR���t�B�O�ƃ����L���O�V�[���B
// ���C���ȊO�̂قڑS�āH
//=============================================================
class CSceneTitle : public CSceneBase
{
public:
	CSceneTitle();
	~CSceneTitle();

	void Update();
	void Draw();
	void Init(CSystemScene *_system);
	void UnInit();
private:
	// �t�F�[�Y(0:�^�C�g��, 1:�R���t�B�O, 2:�����L���O)
	int phase;
	// �X�e�b�v(�t�F�[�Y���̂���Ȃ镪��p)
	int step;
	// �I�����p
	int index;
	// �E�F�C�g�ϐ�
	int wait;
	// �o�ߎ��ԕϐ�
	int time;
	// �f���ɖ߂�p
	int demo_time;

	// �w�iID
	int backID;
	// �^�C�g����ID
	int titleID;
	// ���j���[��ID
	int menuID[4];
	// �t�H���gID
	int fontID;
	// �p�[�e�B�N��
	int particleID;

	// ����SE
	int decideID;
	// �L�����Z��SE
	int cancelID;
	// �J�[�\��SE
	int cursorID;

	// BGMID
	int bgmID;

	// �ėp�}�g���b�N�X
	D3DXMATRIXA16 mat;
	D3DXMATRIXA16 mat2;
	// �ėp�J���[
	D3DCOLOR color;
	// �ėp�u�����h
	D3DBLEND blend;
	// �ėp������
	char string[256];
	// �p�[�e�B�N���ʒu�z��
	D3DXVECTOR2 vecParticlePos[32];
	// �p�[�e�B�N���g�嗦
	float particleScaling[32];
};

#endif