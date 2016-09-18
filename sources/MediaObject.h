#ifndef MEDIAOBJECT_H
#define MEDIAOBJECT_H

#include "Dsound.h"

#define MOT_MUSIC 1
#define MOT_SOUND 2

typedef enum _MOSTATUS {
	MOS_PAN = 1,
	MOS_FREQUENCY = 2,
	MOS_VOLUME = 3,
} MOSTATUS;

//=============================================================
// CMediaObject
//-------------------------------------------------------------
// ���f�B�A�I�u�W�F�N�g�B�e�T�E���h�̓ǂݍ��݂ƍĐ����s���B
// ���f�B�A�I�u�W�F�N�g�̊��N���X�B
//=============================================================
class CMediaObject
{
public:
	// ����
	virtual void Create(const char* filename, LPDIRECTSOUND8 pDSound) = 0;
	// �j��
	virtual void Destroy() = 0;
	// �I�u�W�F�N�g�^�C�v�̎擾
	int GetObjectType() { return objectType; }
	// ���O�̎擾
	LPSTR GetName() { return name; }
protected:
	int objectType;
	LPSTR name;
};

//=============================================================
// CObjectMusic
//-------------------------------------------------------------
// BGM�̃X�g���[�~���O�Đ����s���I�u�W�F�N�g�B
// �o�b�t�@�͍ŏ��ɗ}���āA�����t�@�C���ǂݍ��݂�����B
//=============================================================
class CObjectMusic : public CMediaObject
{
public:
	void Create(const char* filename, LPDIRECTSOUND8 pDSound);
	void Destroy();

	void Play(DWORD start);
	void Restart();
	void Stop();

	BYTE* ReadWavFile(DWORD dwOffset);
	void Update();

	LPDIRECTSOUNDBUFFER pDsoundBuffer;
	//�ʒm��ԕ�������WAV�f�[�^��ǂݍ��ލۂɎg�p����
	BYTE* pbWavData;
	// WAV�f�[�^�̃T�C�Y
	DWORD dwDataSize;
	// DirectSound�o�b�t�@�̃T�C�Y
	DWORD dwBufferSize;
	// �ʒm��
	DWORD dwNumNotify;
	// �ʒm�𔭐�����Ԋu�̃o�C�g�T�C�Y
	DWORD dwNotifySize;
	//WAV�t�@�C���̃w�b�_�[�������������g�`�f�[�^�����܂ł̃I�t�Z�b�g
	DWORD dwDataOffset;

	// �o�b�t�@���Đ��J�[�\��
	DWORD dwCurPlay;
	// �t�@�C�����ǂݍ��݃J�[�\��
	DWORD dwCurRead;
	// DirectSound�o�b�t�@�[���A���ɏ������ރI�t�Z�b�g
	DWORD dwNextOffset;
	// WAV�f�[�^���Ō�܂œǂݍ��񂾂Ƃ���TRUE�ɂȂ�
	BOOL boEndOfData;

	// ���s�[�g
	bool repeat_f;
};

//=============================================================
// CObjectSound
//-------------------------------------------------------------
// SE�̍Đ����s���I�u�W�F�N�g�B
// wav�f�[�^�͑S�ă�������Ɉڂ��B
//=============================================================
class CObjectSound : public CMediaObject
{
public:
	void Create(const char* filename, LPDIRECTSOUND8 pDSound);
	void Destroy();

	void Play();
	void Stop();

	LPDIRECTSOUNDBUFFER pDsoundBuffer;
};

#endif
