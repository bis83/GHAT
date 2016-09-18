#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9.h>

//=============================================================
// CCamera
//-------------------------------------------------------------
// �J�����̃N���X�B
// �f�o�C�X�ւ̃Z�b�g���s���B
//=============================================================
class CCamera
{
public:
	CCamera();
	~CCamera();
	void Init();
	void SetVecEyePt(D3DXVECTOR3 vec);
	void SetVecLookatPt(D3DXVECTOR3 vec);
	void SetVecUpVec(D3DXVECTOR3 vec);
	void SetFieldOfView(float rad);
	void SetAspect(LPDIRECT3DDEVICE9 pDevice);
	void SetRenderingRange(float nearLimit, float farLimit);

	// �f�o�C�X�ւ̃��C�g�̐ݒ�
	void SetCamera(LPDIRECT3DDEVICE9 pDevice);
	// �r���[�s��̎擾
	LPD3DXMATRIX GetViewMatrix();
	// �r���{�[�h�p�s��̎擾
	LPD3DXMATRIX GetBillboardMatrix();
private:
	// �r���[�}�g���b�N�X
	D3DXMATRIXA16 matView;
	D3DXVECTOR3 vecEyePt;
	D3DXVECTOR3 vecLookatPt;
	D3DXVECTOR3 vecUpVec;
	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIXA16 matProj;
	float fovY;
	float aspect;
	float nearPlane, farPlane;
	// �r���{�[�f�B���O�p�r���[�t�s��
	D3DXMATRIXA16 matBillboard;
};

#endif
