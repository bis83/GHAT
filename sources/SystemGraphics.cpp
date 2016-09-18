#include "SystemGraphics.h"
#include "SystemScene.h"
#include "SafeRelease.h"

CSystemGraphics::CSystemGraphics(CGameHolding *_holding, HWND hWnd)
: CSystemBase(_holding)
{
	// Duirect3D�̏�����
	if(FAILED(InitD3d(hWnd)))
	{
		MessageBox(0, "Direct3D�̏������Ɏ��s", "", MB_OK);
		return;
	}

	// �X�v���C�g�̏�����
	if(FAILED(D3DXCreateSprite(pDevice, &pSprite)))
	{
		MessageBox(0, "Sprite�̏������Ɏ��s", "", MB_OK);
	}

	// �e�X�e�[�^�X�̏�����
	drawObjectVector.clear();
	renderMgr.SetDevice(pDevice);
	renderMgr.SetSprite(pSprite);
	camera.Init();
	camera.SetAspect(pDevice);
	light.Init(D3DLIGHT_DIRECTIONAL);
	scene_f = false;

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	// �A���t�@�u�����h
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	// �e�N�X�`���u�����h
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	// �e�N�X�`���X�e�[�W
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
}

CSystemGraphics::~CSystemGraphics()
{
	ClearDrawObject();
	SAFE_RELEASE(pSprite);
	SAFE_RELEASE(pDevice);
	SAFE_RELEASE(pD3d);
}

HRESULT CSystemGraphics::InitD3d(HWND hWnd)
{
	if( NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferWidth = 1280;
	d3dpp.BackBufferHeight = 720;
	// �N�����Ƀt���X�N���[���������肷��
	if(MessageBox(NULL, "�t���X�N���[�����[�h�ŋN�����܂����H", "�m�F", MB_YESNO) == 6)
	{
		D3DDISPLAYMODE d3ddm;
		ZeroMemory(&d3ddm, sizeof(D3DDISPLAYMODE));
		pD3d->GetAdapterDisplayMode(NULL, &d3ddm);
		d3dpp.BackBufferFormat = d3ddm.Format;
		d3dpp.Windowed = FALSE;
		d3dpp.FullScreen_RefreshRateInHz = 60;
	} else {
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.Windowed = TRUE;
	}
	// �f�o�C�X�̐���
	if(FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &pDevice)))
	{
		if(FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &pDevice)))
		{
			if(FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &pDevice)))
			{
				if(FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &pDevice)))
				{
					return E_FAIL;
				}
			}
		}
	}
	return S_OK;
}

void CSystemGraphics::Draw()
{
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
	if(SUCCEEDED(pDevice->BeginScene()))
	{
		scene_f = true;
		// �J�����̐ݒ�
		camera.SetCamera(pDevice);
		renderMgr.SetCamera(&camera);
		// ���C�g�̐ݒ�
		light.SetLight(pDevice, 0);

		// �V�[���ɕ`�揈����C����
		GetScene()->Draw();

		pDevice->EndScene();
		scene_f = false;
	}
	pDevice->Present(NULL, NULL, NULL, NULL);
}

void CSystemGraphics::Reflesh()
{
	// �f�o�C�X�̍Ď擾

	// �f�o�C�X�X�e�[�g�̍Đݒ�

	// �e�I�u�W�F�N�g�̍Ď擾
}

void CSystemGraphics::CreateDrawObject(const char *filename, int objectType)
{
	for(int i=0; i<drawObjectVector.size(); i++)
	{
		if(!strcmp(filename, drawObjectVector[i]->GetName()))
		{
			return;
		}
	}

	if(objectType == DOT_MESH)
	{
		CObjectMesh *obj = new CObjectMesh();
		obj->Create(filename, pDevice);
		for(int i=0; i<drawObjectVector.size(); i++)
		{
			if(drawObjectVector[i] == NULL)
			{
				drawObjectVector[i] = obj;
				return;
			}
		}
		drawObjectVector.push_back(obj);
		return;
	}

	if(objectType == DOT_SPRITE)
	{
		CObjectSprite *obj = new CObjectSprite();
		obj->Create(filename, pDevice);
		for(int i=0; i<drawObjectVector.size(); i++)
		{
			if(drawObjectVector[i] == NULL)
			{
				drawObjectVector[i] = obj;
				return;
			}
		}
		drawObjectVector.push_back(obj);
		return;
	}

	if(objectType == DOT_FONT)
	{
		CObjectFont *obj = new  CObjectFont();
		obj->Create(filename, pDevice);
		for(int i=0; i<drawObjectVector.size(); i++)
		{
			if(drawObjectVector[i] == NULL)
			{
				drawObjectVector[i] = obj;
				return;
			}
		}
		drawObjectVector.push_back(obj);
		return;
	}
}

void CSystemGraphics::DestroyDrawObject(const char *filename)
{
	for(int i=0; i<drawObjectVector.size(); i++)
	{
		if(drawObjectVector[i] != NULL)
		{
			if(!strcmp(drawObjectVector[i]->GetName(), filename))
			{
				drawObjectVector[i]->Destroy();
				SAFE_DELETE(drawObjectVector[i]);
			}
		}
	}
}

void CSystemGraphics::DestroyDrawObject(int id)
{
	if(id-1<0) return;
	if(drawObjectVector[id-1] != NULL)
	{
		drawObjectVector[id-1]->Destroy();
		SAFE_DELETE(drawObjectVector[id-1]);
	}
}

void CSystemGraphics::ClearDrawObject()
{
	for(int i=0; i<drawObjectVector.size(); i++)
	{
		if(drawObjectVector[i] != NULL)
		{
			drawObjectVector[i]->Destroy();
			SAFE_DELETE(drawObjectVector[i]);
		}
	}
	drawObjectVector.clear();
}

CCamera* CSystemGraphics::GetCamera()
{
	return &camera;
}

CLight* CSystemGraphics::GetLight()
{
	return &light;
}

int CSystemGraphics::GetDrawObjectID(const char *filename)
{
	for(int i=0; i<drawObjectVector.size(); i++)
	{
		if(drawObjectVector[i] != NULL)
		{
			if(!strcmp(drawObjectVector[i]->GetName(), filename))
			{
				// ID��vector��index+1��Ԃ�
				return i+1;
			}
		}
	}
	return NULL;
}

void CSystemGraphics::SetDrawObjectStatus(int id, DOSTATUS status, void *pValue)
{
	if(id < 1 || id > drawObjectVector.size())
	{
		return;
	}
	if(drawObjectVector[id-1] == NULL)
	{
		return;
	}
	switch(status)
	{
	case DOS_MATRIX:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_MESH:
			((CObjectMesh*)drawObjectVector[id-1])->matWorld = *((D3DXMATRIXA16*)pValue);
			break;
		case DOT_SPRITE:
			((CObjectSprite*)drawObjectVector[id-1])->matWorld = *((D3DXMATRIXA16*)pValue);
			break;
		case DOT_FONT:
			((CObjectFont*)drawObjectVector[id-1])->matWorld = *((D3DXMATRIXA16*)pValue);
			break;
		}
		break;
	case DOS_SRCBLEND:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_MESH:
			((CObjectMesh*)drawObjectVector[id-1])->srcBlend = *((D3DBLEND*)pValue);
			break;
		case DOT_SPRITE:
			((CObjectSprite*)drawObjectVector[id-1])->srcBlend = *((D3DBLEND*)pValue);
			break;
		case DOT_FONT:
			((CObjectFont*)drawObjectVector[id-1])->srcBlend = *((D3DBLEND*)pValue);
			break;
		}
		break;
	case DOS_DESTBLEND:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_MESH:
			((CObjectMesh*)drawObjectVector[id-1])->destBlend = *((D3DBLEND*)pValue);
			break;
		case DOT_SPRITE:
			((CObjectSprite*)drawObjectVector[id-1])->destBlend = *((D3DBLEND*)pValue);
			break;
		case DOT_FONT:
			((CObjectFont*)drawObjectVector[id-1])->destBlend = *((D3DBLEND*)pValue);
			break;
		}
		break;
	case DOS_BILLBOARD:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_MESH:
			((CObjectMesh*)drawObjectVector[id-1])->billboarding = *((BOOL*)pValue);
			break;
		case DOT_SPRITE:
			((CObjectSprite*)drawObjectVector[id-1])->billboarding = *((BOOL*)pValue);
			break;
		}
		break;
	case DOS_CULL:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_MESH:
			((CObjectMesh*)drawObjectVector[id-1])->cullMode = *((D3DCULL*)pValue);
			break;
		}
		break;
	case DOS_SHADE:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_MESH:
			((CObjectMesh*)drawObjectVector[id-1])->shadeMode = *((D3DSHADEMODE*)pValue);
			break;
		}
		break;
	case DOS_FILL:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_MESH:
			((CObjectMesh*)drawObjectVector[id-1])->fillMode = *((D3DFILLMODE*)pValue);
			break;
		}
		break;
	case DOS_EFFECT:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_MESH:
			((CObjectMesh*)drawObjectVector[id-1])->effectID = *((int*)pValue);
			break;
		}
		break;
	case DOS_COLOR:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_SPRITE:
			((CObjectSprite*)drawObjectVector[id-1])->color = *((D3DCOLOR*)pValue);
			break;
		case DOT_FONT:
			((CObjectFont*)drawObjectVector[id-1])->color = *((D3DCOLOR*)pValue);
			break;
		}
		break;
	case DOS_SIZE:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_SPRITE:
			((CObjectSprite*)drawObjectVector[id-1])->SetSize(*((int*)pValue), *(((int*)pValue)+1));
			break;
		case DOT_FONT:
			((CObjectFont*)drawObjectVector[id-1])->SetSize(*((int*)pValue), *(((int*)pValue)+1));
		}
		break;
	case DOS_STRING:
		switch(drawObjectVector[id-1]->GetObjectType())
		{
		case DOT_FONT:
			((CObjectFont*)drawObjectVector[id-1])->str = (char*)pValue;
			break;
		}
		break;
	}
}

void CSystemGraphics::DrawObject(int id)
{
	if(!Drawing())
	{
		return;
	}
	if(id < 1 || id > drawObjectVector.size())
	{
		return;
	}
	if(drawObjectVector[id-1] == NULL)
	{
		return;
	}
	renderMgr.Draw(drawObjectVector[id-1]);
}

bool CSystemGraphics::Drawing()
{
	return scene_f;
}
