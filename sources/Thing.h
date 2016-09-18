#ifndef THING_H
#define THING_H

#include <d3dx9.h>
#include "DrawObject.h"
#include "HandleSystem.h"

//=============================================================
// CThing
//-------------------------------------------------------------
// ���N���X�̊��N���X�B
// �I�u�W�F�N�g��`�悷��ۂɕK�v�ȃX�e�[�^�X�𕪂���₷�����B
//=============================================================
class CThing
{
public:
	CThing();

	// �O���t�B�b�N�X�ւ̃|�C���^��n���ƕ`�揈�����s��
	virtual void DrawThing(CHandleGraphics* hGrap) = 0;
	// �����Z�b�g�A�b�v
	virtual void Set(const char* filename, CHandleGraphics* hGrap) = 0;

	// ������
	void InitMatrix();
	// 3��ނ̃x�N�g������s����X�V����
	void SetMatrix();

	// �I�u�W�F�N�gID
	int objectID;
	// ���[���h�s��
	D3DXVECTOR3 vecPos;
	D3DXVECTOR3 vecScale;
	D3DXVECTOR3 vecRot;
	D3DXMATRIXA16 matWorld;
};

//=============================================================
// CThingMesh
//-------------------------------------------------------------
// ���b�V���p�̏���ǉ��������N���X�B
//=============================================================
class CThingMesh : public CThing
{
public:
	CThingMesh();

	void DrawThing(CHandleGraphics *hGrap);
	void Set(const char* filename, CHandleGraphics *hGrap);

	// �u�����h�^�C�v(0:�ʏ�,1:���@)
	int blendType;
	// �r���{�[�h�t���O
	bool billBoarding;
	// �J�����O���[�h(0:NONE, 1:CW, 2:CCW)
	int culling;
	// �V�F�[�f�B���O���[�h(0:�O�[���[,1:�t���b�g)
	int shadeMode;
	// �t�B�����[�h(0:�\���b�h, 1:���C���t���[��, 2:�|�C���g)
	int fillMode;
	// �G�t�F�N�g(������)
	int effectMode;
};

//=============================================================
// CThingSprite
//-------------------------------------------------------------
// �X�v���C�g�p�̏���ǉ��������N���X�B
//=============================================================
class CThingSprite : public CThing
{
public:
	CThingSprite();

	void DrawThing(CHandleGraphics *hGrap);
	void Set(const char *filename, CHandleGraphics *hGrap);

	BYTE a, r, g, b;
	// �u�����h�^�C�v(0:�ʏ�,1:���@)
	int blendType;
	// �r���{�[�h
	BOOL billBoard;
};

#endif