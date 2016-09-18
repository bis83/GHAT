#include "Camera.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

void CCamera::Init()
{
	D3DXMatrixIdentity(&matView);
	vecEyePt = D3DXVECTOR3(0.0f, 0.0f, -3.0f);
	vecLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	fovY = D3DX_PI/4;
	aspect = 1.0f;
	nearPlane = 1.0f;
	farPlane = 1000.0f;
}

void CCamera::SetVecEyePt(D3DXVECTOR3 vec)
{
	vecEyePt = vec;
}

void CCamera::SetVecLookatPt(D3DXVECTOR3 vec)
{
	vecLookatPt = vec;
}

void CCamera::SetVecUpVec(D3DXVECTOR3 vec)
{
	vecUpVec = vec;
}

void CCamera::SetFieldOfView(float rad)
{
	fovY = rad;
}

void CCamera::SetAspect(LPDIRECT3DDEVICE9 pDevice)
{
	D3DVIEWPORT9 vp;
	if(FAILED(pDevice->GetViewport(&vp)))
	{
		return;
	}
	aspect = (float)vp.Width / (float)vp.Height;
}

void CCamera::SetRenderingRange(float nearLimit, float farLimit)
{
	nearPlane = nearLimit;
	farPlane = farLimit;
}

void CCamera::SetCamera(LPDIRECT3DDEVICE9 pDevice)
{
	// セットされたベクトルからビュー行列を計算
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	pDevice->SetTransform(D3DTS_VIEW, &matView);
	
	// ビルボーディング用に逆行列を計算する
	D3DXMatrixInverse(&matBillboard, NULL, &matView);
	matBillboard._41=0;
	matBillboard._42=0;
	matBillboard._43=0;

	// プロジェクション行列を設定
	D3DXMatrixPerspectiveFovLH(&matProj, fovY, aspect, nearPlane, farPlane);
	pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

LPD3DXMATRIX CCamera::GetViewMatrix()
{
	return &matView;
}

LPD3DXMATRIX CCamera::GetBillboardMatrix()
{
	return &matBillboard;
}