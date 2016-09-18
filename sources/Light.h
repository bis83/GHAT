#ifndef LIGHT_H
#define LIGHT_H

#include <d3dx9.h>

//=============================================================
// CLight
//-------------------------------------------------------------
// D3DLIGHT���B������N���X�B
// �f�o�C�X�ւ̃��C�g�̃Z�b�g���s���B
//==============================================================
class CLight
{
public:
	CLight();
	~CLight();
	void Init(D3DLIGHTTYPE type);
	void SetDiffuse(float r, float g, float b, float a);
	void SetAmbient(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void SetLightType(D3DLIGHTTYPE type);
	void SetAttenuation(float a);
	void SetPosition(D3DXVECTOR3 vec);
	void SetDirection(D3DXVECTOR3 vec);
	void SetRange(float r);
	void SetFalloff(float f);
	void SetCorn(float theta, float phi);

	// �f�o�C�X�ւ̃J�����̐ݒ�
	void SetLight(LPDIRECT3DDEVICE9 pDevice, int index);
private:
	D3DLIGHT9 light;
};

#endif