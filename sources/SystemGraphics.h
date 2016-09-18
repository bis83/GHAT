#ifndef SYSTEMGRAPHICS_H
#define SYSTEMGRAPHICS_H

#include <windows.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "GameHolding.h"
#include "DrawObject.h"
#include "Light.h"
#include "Camera.h"
#include "RenderingManager.h"

#include <vector>
using namespace std;

//=============================================================
// CSystemGraphics
//-------------------------------------------------------------
// �O���t�B�b�N�X�Ɋւ���S�Ă̏����𓝊�����N���X�B
// Draw�𖈃t���[���Ăяo���ĕ`��C�x���g�L���[����������B
//=============================================================
class CSystemGraphics : public CSystemBase
{
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CSystemGraphics(CGameHolding* _holding, HWND hWnd);
	~CSystemGraphics();
	// �`��
	void Draw();
	// ���t���b�V��
	void Reflesh();

	// �`��I�u�W�F�N�g�̍쐬
	void CreateDrawObject(const char* filename, int objectType);
	// �`��I�u�W�F�N�g�̍폜
	void DestroyDrawObject(const char* filename);
	void DestroyDrawObject(int id);
	// �`��I�u�W�F�N�g�̑S�폜
	void ClearDrawObject();

	// �J�����̎擾
	CCamera* GetCamera();
	// ���C�g�̎擾
	CLight* GetLight();
	// �`��I�u�W�F�N�gID�̎擾
	int GetDrawObjectID(const char* filename);
	// �`��I�u�W�F�N�g�̃X�e�[�^�X��ݒ�
	void SetDrawObjectStatus(int id, DOSTATUS status, void* pValue);
	// �`��I�u�W�F�N�g�̕`��(�V�[����Draw���̂�)
	void DrawObject(int id);

	// �`�撆���̔���
	bool Drawing();
private:
	// Direct3D�̏�����
	HRESULT InitD3d(HWND hWnd);

	// Direct3D
	LPDIRECT3D9 pD3d;
	// �f�o�C�X
	LPDIRECT3DDEVICE9 pDevice;
	// �f�o�C�X�p�����[�^
	D3DPRESENT_PARAMETERS d3dpp;
	// �X�v���C�g
	LPD3DXSPRITE pSprite;

	// �����_�����O�}�l�[�W���[
	CRenderingManager renderMgr;

	// �`��I�u�W�F�N�g���X�g
	vector<CDrawObject*> drawObjectVector;
	// �`��G�t�F�N�g���X�g(����͖������H)
	//vector<int> drawEffectVector;

	// �J����
	CCamera camera;
	// ���C�g
	CLight light;

	// �V�[���̊J�n����
	bool scene_f;
};

#endif
