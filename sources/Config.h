#ifndef CONFIG_H
#define CONFIG_H

//=============================================================
// CConfig
//-------------------------------------------------------------
// �R���t�B�O�̏��������N���X�B
//=============================================================
class CConfig
{
public:
	// �R���X�g���N�^
	CConfig();

	// �t�@�C������̓ǂݍ���
	void LoadFile();
	// �t�@�C���ւ̏����o��
	void SaveFile();

	int key_ok;
	int key_cancel;
	int key_shot;
	int key_bomb;
	int key_pause;
	int bgm_volume;
	int se_volume;
	int rest;
	int difficult;
};

extern CConfig e_Config;

#endif
