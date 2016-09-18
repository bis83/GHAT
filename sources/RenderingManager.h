#ifndef RENDERINGMANAGER_H
#define RENDERINGMANAGER_H

#include <d3dx9.h>

#include "DrawObject.h"
#include "Camera.h"

class CRenderingManager
{
public:
	// 描画
	void Draw(CDrawObject* obj);
	// オブジェクトの描画
	void DrawObjectMesh(CObjectMesh* obj);
	void DrawObjectSprite(CObjectSprite* obj);
	void DrawObjectFont(CObjectFont* obj);

	// メッシュコンテナのレンダリング
	void RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	// フレームの描画
	void DrawFrame(LPD3DXFRAME pFrame);
	// ワールド行列の設定
	void SetWorldMatrix(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
private:
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	// スプライトへのポインタ
	LPD3DXSPRITE pSprite;
	// カメラ
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
