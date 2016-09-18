#include "Light.h"

CLight::CLight()
{
	Init(D3DLIGHT_DIRECTIONAL);
}

CLight::~CLight()
{
}

void CLight::Init(D3DLIGHTTYPE type)
{
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = type;
	// Šeƒ‰ƒCƒg‚ÌŽí—Þ‚É‡‚í‚¹‚Ä‰Šú‰»
	switch(light.Type)
	{
	case D3DLIGHT_DIRECTIONAL:
		SetDiffuse(0.1f, 0.1f, 0.1f, 0.5f);
		SetSpecular(0.1f, 0.1f, 0.1f, 1.0f);
		SetAmbient(0.0f, 0.0f, 0.0f, 0.0f);
		SetDirection(D3DXVECTOR3(1, -1, 1));
		break;
	case D3DLIGHT_POINT:
		SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
		SetSpecular(1.0f, 1.0f, 1.0f, 1.0f);
		SetAmbient(1.0f, 1.0f, 1.0f, 1.0f);
		SetAttenuation(1.0f);
		SetPosition(D3DXVECTOR3(0, 0, -1));
		SetRange(10.0f);
		break;
	case D3DLIGHT_SPOT:
		SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
		SetSpecular(1.0f, 1.0f, 1.0f, 1.0f);
		SetAmbient(1.0f, 1.0f, 1.0f, 1.0f);
		SetAttenuation(1.0f);
		SetPosition(D3DXVECTOR3(-1, 1, -1));
		SetDirection(D3DXVECTOR3(1, -1, 1));
		SetRange(10.0f);
		SetCorn(D3DX_PI/12, D3DX_PI/10);
		SetFalloff(1.0f);
		break;
	}
}

void CLight::SetAmbient(float r, float g, float b, float a)
{
	light.Ambient.r = r;
	light.Ambient.g = g;
	light.Ambient.b = b;
	light.Ambient.a = a;
}

void CLight::SetDiffuse(float r, float g, float b, float a)
{
	light.Diffuse.r = r;
	light.Diffuse.g = g;
	light.Diffuse.b = b;
	light.Diffuse.a = a;
}

void CLight::SetSpecular(float r, float g, float b, float a)
{
	light.Specular.r = r;
	light.Specular.g = g;
	light.Specular.b = b;
	light.Specular.a = a;
}

void CLight::SetAttenuation(float a)
{
	light.Attenuation0 = a;
}

void CLight::SetCorn(float theta, float phi)
{
	light.Theta = theta;
	light.Phi = phi;
}

void CLight::SetDirection(D3DXVECTOR3 vec)
{
	light.Direction = vec;
}

void CLight::SetFalloff(float f)
{
	light.Falloff = f;
}

void CLight::SetLightType(D3DLIGHTTYPE type)
{
	light.Type = type;
}

void CLight::SetPosition(D3DXVECTOR3 vec)
{
	light.Position = vec;
}

void CLight::SetRange(float r)
{
	light.Range = r;
}

void CLight::SetLight(LPDIRECT3DDEVICE9 pDevice, int index)
{
	pDevice->SetLight(index, &light);
	pDevice->LightEnable(index, TRUE);
}
