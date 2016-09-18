#ifndef HANDLESYSTEM_H
#define HANDLESYSTEM_H

#include "SystemGraphics.h"
#include "SystemMedia.h"

//=============================================================
// ChandleGraphics
//-------------------------------------------------------------
// �O���t�B�b�N�X�ɃV�[������A�N�Z�X����ۂɎg�p����n���h���N���X
//=============================================================
class CHandleGraphics
{
private:
	CSystemGraphics *graphics;
public:
	// �R���X�g���N�^
	CHandleGraphics(CSystemGraphics *_graphics)
	{
		graphics = _graphics;
	}
	// �`��I�u�W�F�N�g�̍쐬
	void CreateDrawObject(const char* filename, int objectType)
	{
		graphics->CreateDrawObject(filename, objectType);
	}
	// �`��I�u�W�F�N�g�̍폜
	void DestroyDrawObject(const char* filename)
	{
		graphics->DestroyDrawObject(filename);
	}
	void DestroyDrawObject(int id)
	{
		graphics->DestroyDrawObject(id);
	}
	// �`��I�u�W�F�N�g�̑S�폜
	void ClearDrawObject()
	{
		graphics->ClearDrawObject();
	}

	// �J�����̎擾
	CCamera* GetCamera()
	{
		return graphics->GetCamera();
	}
	// ���C�g�̎擾
	CLight* GetLight()
	{
		return graphics->GetLight();
	}
	// �`��I�u�W�F�N�gID�̎擾
	int GetDrawObjectID(const char* filename)
	{
		return graphics->GetDrawObjectID(filename);
	}
	// �`��I�u�W�F�N�g�̃X�e�[�^�X��ݒ�
	void SetDrawObjectStatus(int id, DOSTATUS status, void* pValue)
	{
		graphics->SetDrawObjectStatus(id, status, pValue);
	}
	// �`��I�u�W�F�N�g�̕`��(�V�[����Draw���̂�)
	void DrawObject(int id)
	{
		graphics->DrawObject(id);
	}
};

//=============================================================
// ChandleMedia
//-------------------------------------------------------------
// ���f�B�A�ɃV�[������A�N�Z�X����ۂɎg�p����n���h���N���X
//=============================================================
class CHandleMedia
{
private:
	CSystemMedia *media;
public:
	CHandleMedia(CSystemMedia *_media)
	{
		media = _media;
	}
	// �����I�u�W�F�N�g�̍쐬
	void CreateMediaObject(const char* filename, int objectType)
	{
		media->CreateMediaObject(filename, objectType);
	}
	// �����I�u�W�F�N�g�̊J��
	void DestroyMediaObject(const char* filename)
	{
		media->DestroyMediaObject(filename);
	}
	void DestroyMediaObject(int id)
	{
		media->DestroyMediaObject(id);
	}
	// �����I�u�W�F�N�g�̑S�폜
	void ClearMediaObject()
	{
		media->ClearMediaObject();
	}

	// BGM�̍Đ�
	void PlayBGM(int id, DWORD start = 0)
	{
		media->PlayBGM(id, start);
	}
	void RestartBGM()
	{
		media->RestartBGM();
	}
	// BGM�̒�~
	void StopBGM()
	{
		media->StopBGM();
	}
	// SE�̍Đ�
	void PlaySE(int id)
	{
		media->PlaySE(id);
	}
	// SE�̑S��~
	void StopSE()
	{
		media->StopSE();
	}
	// �Đ��X�e�[�^�X�̕ύX
	void SetPlayStatus(int id, MOSTATUS status, void* pValue)
	{
		media->SetPlayStatus(id, status, pValue);
	}

	// �����I�u�W�F�N�gID�̎擾
	int GetMediaObjectID(const char* filename)
	{
		return media->GetMediaObjectID(filename);
	}
};

#endif