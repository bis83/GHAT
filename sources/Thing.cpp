#include "Thing.h"

CThing::CThing()
{
}

void CThing::InitMatrix()
{
	ZeroMemory(&vecPos, sizeof(D3DXVECTOR3));
	ZeroMemory(&vecScale, sizeof(D3DXVECTOR3));
	ZeroMemory(&vecRot, sizeof(D3DXVECTOR3));
	D3DXMatrixIdentity(&matWorld);
}

void CThing::SetMatrix()
{

	D3DXMATRIXA16 mScale;
	D3DXMATRIXA16 mRot;
	D3DXMATRIXA16 mTrans;

	D3DXMatrixScaling(&mScale, vecScale.x, vecScale.y, vecScale.z);

	D3DXMatrixRotationYawPitchRoll(&mRot, vecRot.y, vecRot.x, vecRot.z);

	D3DXMatrixTranslation(&mTrans, vecPos.x, vecPos.y, vecPos.z);

	matWorld = mScale*mRot*mTrans;
}

CThingMesh::CThingMesh()
{
	InitMatrix();

	objectID = 0;
	blendType = 0;
	billBoarding = false;
	culling = 0;
	shadeMode = 0;
	fillMode = 0;
	effectMode = 0;
}

void CThingMesh::DrawThing(CHandleGraphics *hGrap)
{
	// �}�g���N�X�̐ݒ�
	SetMatrix();
	hGrap->SetDrawObjectStatus(objectID, DOS_MATRIX, &matWorld);
	// �u�����h�l�̐ݒ�
	D3DBLEND blend;
	switch(blendType)
	{
	case 1:		// ���Z
		blend = D3DBLEND_SRCALPHA;
		hGrap->SetDrawObjectStatus(objectID, DOS_SRCBLEND, &blend);
		blend = D3DBLEND_ONE;
		hGrap->SetDrawObjectStatus(objectID, DOS_DESTBLEND, &blend);
		break;
	}
	// �r���{�[�h�̐ݒ�
	BOOL bb;
	if(billBoarding)
	{
		bb = TRUE;
		hGrap->SetDrawObjectStatus(objectID, DOS_BILLBOARD, &bb);
	}
	// �J�����O�̐ݒ�
	D3DCULL cull;
	switch(culling)
	{
	case 1:
		cull = D3DCULL_CW;
		hGrap->SetDrawObjectStatus(objectID, DOS_CULL, &cull);
		break;
	case 2:
		cull = D3DCULL_CCW;
		hGrap->SetDrawObjectStatus(objectID, DOS_CULL, &cull);
		break;
	}
	// �V�F�[�h���[�h�̐ݒ�
	D3DSHADEMODE shade;
	switch(shadeMode)
	{
	case 1:
		shade = D3DSHADE_FLAT;
		hGrap->SetDrawObjectStatus(objectID, DOS_SHADE, &shade);
		break;
	}
	// �t�B�����[�h�̐ݒ�
	D3DFILLMODE fil;
	switch(fillMode)
	{
	case 1:
		fil = D3DFILL_WIREFRAME;
		hGrap->SetDrawObjectStatus(objectID, DOS_FILL, &fil);
		break;
	case 2:
		fil = D3DFILL_POINT;
		hGrap->SetDrawObjectStatus(objectID, DOS_FILL, &fil);
		break;
	}
	// �`��
	hGrap->DrawObject(objectID);
}

void CThingMesh::Set(const char *filename, CHandleGraphics *hGrap)
{
	objectID = hGrap->GetDrawObjectID(filename);
}

CThingSprite::CThingSprite()
{
	InitMatrix();

	objectID = 0;
	a = r = g = b = 0xff;
	blendType = 0;
	billBoard = FALSE;
}

void CThingSprite::DrawThing(CHandleGraphics *hGrap)
{
	// �}�g���b�N�X�̐ݒ�
	SetMatrix();
	hGrap->SetDrawObjectStatus(objectID, DOS_MATRIX, &matWorld);
	// �J���[�̐ݒ�
	D3DCOLOR color = D3DCOLOR_RGBA(r, g, b, a);
	hGrap->SetDrawObjectStatus(objectID, DOS_COLOR, &color);
	// �u�����h�̐ݒ�
	D3DBLEND blend;
	switch(blendType)
	{
	case 1:		// ���Z
		blend = D3DBLEND_SRCALPHA;
		hGrap->SetDrawObjectStatus(objectID, DOS_SRCBLEND, &blend);
		blend = D3DBLEND_ONE;
		hGrap->SetDrawObjectStatus(objectID, DOS_DESTBLEND, &blend);
		break;
	}
	// �r���{�[�h�ݒ�
	hGrap->SetDrawObjectStatus(objectID, DOS_BILLBOARD, &billBoard);
	// �`��
	hGrap->DrawObject(objectID);
}

void CThingSprite::Set(const char *filename, CHandleGraphics *hGrap)
{
	objectID = hGrap->GetDrawObjectID(filename);
}
