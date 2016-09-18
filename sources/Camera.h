#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9.h>

//=============================================================
// CCamera
//-------------------------------------------------------------
// カメラのクラス。
// デバイスへのセットも行う。
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

	// デバイスへのライトの設定
	void SetCamera(LPDIRECT3DDEVICE9 pDevice);
	// ビュー行列の取得
	LPD3DXMATRIX GetViewMatrix();
	// ビルボード用行列の取得
	LPD3DXMATRIX GetBillboardMatrix();
private:
	// ビューマトリックス
	D3DXMATRIXA16 matView;
	D3DXVECTOR3 vecEyePt;
	D3DXVECTOR3 vecLookatPt;
	D3DXVECTOR3 vecUpVec;
	// プロジェクションマトリックス
	D3DXMATRIXA16 matProj;
	float fovY;
	float aspect;
	float nearPlane, farPlane;
	// ビルボーディング用ビュー逆行列
	D3DXMATRIXA16 matBillboard;
};

#endif
