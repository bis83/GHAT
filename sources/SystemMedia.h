#ifndef SYSTEMMEDIA_H
#define SYSTEMMEDIA_H

#include "GameHolding.h"
#include "MediaObject.h"

#include <Dsound.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")

#include <vector>

using namespace std;

class CSystemMedia : public CSystemBase
{
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CSystemMedia(CGameHolding* _holding, HWND hWnd);
	~CSystemMedia();
	// �X�V
	void Update();

	// �����I�u�W�F�N�g�̍쐬
	void CreateMediaObject(const char* filename, int objectType);
	// �����I�u�W�F�N�g�̊J��
	void DestroyMediaObject(const char* filename);
	void DestroyMediaObject(int id);
	// �����I�u�W�F�N�g�̑S�폜
	void ClearMediaObject();

	// BGM�̍Đ�
	void PlayBGM(int id, DWORD start = 0);
	// BGM�̍ĊJ
	void RestartBGM();
	// BGM�̒�~
	void StopBGM();
	// SE�̍Đ�
	void PlaySE(int id);
	// SE�̑S��~
	void StopSE();
	// �Đ��X�e�[�^�X�̕ύX
	void SetPlayStatus(int id, MOSTATUS status, void* pValue);

	// �����I�u�W�F�N�gID�̎擾
	int GetMediaObjectID(const char* filename);
private:
	// ������
	HRESULT InitDSound(HWND hWnd);

	// DirectSoundObject
	LPDIRECTSOUND8 pDSound;

	// ���f�B�A�I�u�W�F�N�g���X�g
	vector<CMediaObject*> mediaObjectVector;
	// �Đ���BGM��ID
	int playingMusicID;
};

#endif
