#include "RenderingManager.h"
#include "MyMesh.h"

void CRenderingManager::Draw(CDrawObject *obj)
{
	switch(obj->GetObjectType())
	{
	case DOT_MESH:
		DrawObjectMesh((CObjectMesh*)obj);
		break;
	case DOT_SPRITE:
		DrawObjectSprite((CObjectSprite*)obj);
		break;
	case DOT_FONT:
		DrawObjectFont((CObjectFont*)obj);
		break;
	}
}

// ���b�V���̕`��
void CRenderingManager::DrawObjectMesh(CObjectMesh* obj)
{
	// �e�탌���_�[�X�e�[�g�ݒ�
	pDevice->SetRenderState(D3DRS_FILLMODE, obj->fillMode);
	pDevice->SetRenderState(D3DRS_SHADEMODE, obj->shadeMode);
	pDevice->SetRenderState(D3DRS_CULLMODE, obj->cullMode);
	// �u�����h����
	pDevice->SetRenderState(D3DRS_SRCBLEND, obj->srcBlend);
	pDevice->SetRenderState(D3DRS_DESTBLEND, obj->destBlend);
	// �r���{�[�f�B���O����
	if(obj->billboarding)
	{
		D3DXMatrixMultiply(&obj->matWorld, &obj->matWorld, pCam->GetBillboardMatrix());
	}
	pDevice->SetTransform(D3DTS_WORLD, &obj->matWorld);
	for(DWORD i = 0; i<obj->dwNumMaterials; i++)
	{
		pDevice->SetMaterial(&obj->pMeshMaterials[i]);
		pDevice->SetTexture(0, obj->pMeshTextures[i]);
		obj->pMesh->DrawSubset(i);
	}
	//SetWorldMatrix(obj->pFrameRoot, &obj->matWorld);
	//DrawFrame(obj->pFrameRoot);
	// �e�X�e�[�^�X�̏�����
	obj->ResetStatus();
}

// �X�v���C�g�̕`��
void CRenderingManager::DrawObjectSprite(CObjectSprite* obj)
{
	// �r���{�[�h�t���O�����Ă�ƃ��[���h��Ԃɕ`�悷��
	if(obj->billboarding)
	{
		pSprite->SetWorldViewLH(&obj->matWorld, pCam->GetViewMatrix());
		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_BILLBOARD);
	} else {
		pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
	pSprite->SetTransform(&obj->matWorld);
	pDevice->SetRenderState(D3DRS_SRCBLEND, obj->srcBlend);
	pDevice->SetRenderState(D3DRS_DESTBLEND, obj->destBlend);
	pSprite->Draw(obj->pTexture, &obj->rect, &obj->vecCenter,
		NULL, obj->color);
	// �e�X�e�[�^�X�̏�����
	obj->ResetStatus();
	pSprite->End();
}

void CRenderingManager::DrawObjectFont(CObjectFont* obj)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pDevice->SetRenderState(D3DRS_SRCBLEND, obj->srcBlend);
	pDevice->SetRenderState(D3DRS_DESTBLEND, obj->destBlend);
	int temp = 0;
	float theta = asin(obj->matWorld._12);
	for(int i=0; obj->str[i] != '\0'; i++)
	{
		// �����̎擾
		temp = obj->c[obj->str[i]];
		obj->rect.top = ((temp-1)/16)*obj->c_height;
		obj->rect.bottom = obj->rect.top + obj->c_height;
		obj->rect.left = ((temp-1)%16)*obj->c_width;
		obj->rect.right = obj->rect.left + obj->c_width;

		// ���[���h�s��̐ݒ�
		pSprite->SetTransform(&obj->matWorld);
		// �`��
		pSprite->Draw(obj->pTexture, &obj->rect, NULL, NULL, obj->color);
		// ���̕`��̂��߂Ɉʒu�����炷
		obj->matWorld._41 += obj->c_width * cos(theta);
		obj->matWorld._42 += obj->c_height * sin(theta);
	}
	obj->ResetStatus();
	pSprite->End();
}

void CRenderingManager::DrawFrame(LPD3DXFRAME pFrame)
{
	LPD3DXMESHCONTAINER pMeshContainer;
	pMeshContainer = pFrame->pMeshContainer;
	while(pMeshContainer != NULL)
	{
		RenderMeshContainer(pMeshContainer, pFrame);
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	if(pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pFrame->pFrameSibling);
	}

	if(pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pFrame->pFrameFirstChild);
	}
}

void CRenderingManager::RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{
	SMeshContainer* pMeshContainer = (SMeshContainer*)pMeshContainerBase;
	SMeshFrame* pFrame = (SMeshFrame*)pFrameBase;
	UINT iMaterial;

	pDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);

	for(iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
	{
		pDevice->SetMaterial(&pMeshContainer->pMaterials[iMaterial].MatD3D);
		pDevice->SetTexture(0, pMeshContainer->ppTextures[iMaterial]);
		pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial);
	}
}

void CRenderingManager::SetWorldMatrix(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	SMeshFrame* pFrame = (SMeshFrame*)pFrameBase;

	if(pParentMatrix != NULL)
	{
		D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
	} else {
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}

	if(pFrame->pFrameSibling != NULL)
	{
		SetWorldMatrix(pFrame->pFrameSibling, pParentMatrix);
	}

	if(pFrame->pFrameFirstChild != NULL)
	{
		SetWorldMatrix(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
	}
}
