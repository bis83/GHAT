#ifndef RENDERINGMANAGER_H
#define RENDERINGMANAGER_H

#include <d3dx9.h>

#include "DrawObject.h"
#include "Camera.h"

class CRenderingManager
{
public:
	// �`��
	void Draw(CDrawObject* obj);
	// �I�u�W�F�N�g�̕`��
	void DrawObjectMesh(CObjectMesh* obj);
	void DrawObjectSprite(CObjectSprite* obj);
	void DrawObjectFont(CObjectFont* obj);

	// ���b�V���R���e�i�̃����_�����O
	void RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	// �t���[���̕`��
	void DrawFrame(LPD3DXFRAME pFrame);
	// ���[���h�s��̐ݒ�
	void SetWorldMatrix(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
private:
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	// �X�v���C�g�ւ̃|�C���^
	LPD3DXSPRITE pSprite;
	// �J����
	CCamera *pCam;
public:
	void SetDevice(LPDIRECT3DDEVICE9 pd)
	{
		pDevice = pd;
	}
	void SetSprite(LPD3DXSPRITE ps)
	{
		pSprite = ps;
	}
	void SetCamera(CCamera *camera_p)
	{
		pCam = camera_p;
	}
};

#endif
