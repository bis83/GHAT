#include "DrawObject.h"
#include "MyMesh.h"
#include "RenderingManager.h"
#include "Hierarchy.h"

#include "SafeRelease.h"

#include <iostream>
#include <fstream>
using namespace std;

// メッシュオブジェクト
void CObjectMesh::Create(const char* filename, LPDIRECT3DDEVICE9 pDevice)
{
	objectType = DOT_MESH;
	name = new TCHAR[strlen(filename)+1];
	strcpy(name, filename);

	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	if(FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pD3DXMtrlBuffer, NULL, &dwNumMaterials, &pMesh)))
	{
		MessageBox(NULL, "メッシュの読み込みに失敗", name, MB_OK);
	}
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pMeshMaterials = new D3DMATERIAL9[dwNumMaterials];
	pMeshTextures = new LPDIRECT3DTEXTURE9[dwNumMaterials];
	for(DWORD i=0; i<dwNumMaterials; i++)
	{
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;
		pMeshTextures[i] = NULL;
		if(d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if(FAILED(D3DXCreateTextureFromFile(pDevice, d3dxMaterials[i].pTextureFilename, &pMeshTextures[i])))
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗", name, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();
	/*if(FAILED(D3DXLoadMeshHierarchyFromX(filename, D3DXMESH_MANAGED, pDevice, &e_Hierarchy,
		NULL, &pFrameRoot, &pAnimeController)))
	{
		MessageBox(NULL, "メッシュの読み込みに失敗", name, MB_OK);
	}*/
	// 描画ステータスの初期化
	ResetStatus();
}

void CObjectMesh::Destroy()
{
	SAFE_DELETE_ARRAY(name);
	SAFE_RELEASE(pMesh);
	SAFE_DELETE_ARRAY(pMeshMaterials);
	for(DWORD i=0; i<dwNumMaterials; i++)
	{
		SAFE_RELEASE(pMeshTextures[i]);
	}
}

void CObjectMesh::ResetStatus()
{
	D3DXMatrixIdentity(&matWorld);
	srcBlend = D3DBLEND_SRCALPHA;
	destBlend = D3DBLEND_INVSRCALPHA;
	billboarding = FALSE;
	cullMode = D3DCULL_CCW;
	fillMode = D3DFILL_SOLID;
	shadeMode = D3DSHADE_GOURAUD;
	effectID = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

// スプライトオブジェクト
void CObjectSprite::Create(const char *filename, LPDIRECT3DDEVICE9 pDevice)
{
	objectType = DOT_SPRITE;
	name = new TCHAR[strlen(filename)+1];
	strcpy(name, filename);

	if(FAILED(D3DXCreateTextureFromFileEx(pDevice, filename, NULL, NULL, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0x00000000, NULL, NULL, &pTexture)))
	{
		MessageBox(NULL, "テクスチャの読み込みに失敗", name, MB_OK);
		return;
	}
	D3DSURFACE_DESC Desc;
	pTexture->GetLevelDesc(0, &Desc);
	vecCenter = D3DXVECTOR3(Desc.Width/2, Desc.Height/2, 0);
	ZeroMemory(&rect, sizeof(RECT));

	// 描画ステータスの初期化
	ResetStatus();
}

void CObjectSprite::Destroy()
{
	SAFE_DELETE_ARRAY(name);
	SAFE_RELEASE(pTexture);
}

void CObjectSprite::SetSize(int width, int height)
{
	rect.right = width;
	rect.bottom = height;
	vecCenter.x = width/2.0;
	vecCenter.y = height/2.0;
}

void CObjectSprite::ResetStatus()
{
	D3DXMatrixIdentity(&matWorld);
	srcBlend = D3DBLEND_SRCALPHA;
	destBlend = D3DBLEND_INVSRCALPHA;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	billboarding = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

// フォントオブジェクト

void CObjectFont::Create(const char *filename, LPDIRECT3DDEVICE9 pDevice)
{
	objectType = DOT_FONT;
	name = new TCHAR[strlen(filename)+1];
	strcpy(name, filename);

	// テクスチャを作成
	if(FAILED(D3DXCreateTextureFromFileEx(pDevice, filename, NULL, NULL, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0x00000000, NULL, NULL, &pTexture)))
	{
		MessageBox(NULL, "テクスチャの読み込みに失敗", name, MB_OK);
		return;
	}
	
	// 文字配列を作成する
	for(int i=0; i<256; i++)
	{
		c[i] = 0;
	}
	ifstream fin("Data/Text/Font.txt");
	char a;
	num_font = 0;
	while(!fin.eof())
	{
		fin >> a;
		if(a != '\n' || a != EOF)
		{
			num_font++;
			c[a] = num_font;
		}
	}
	fin.close();

	// 描画ステータスの初期化
	ResetStatus();
}

void CObjectFont::Destroy()
{
	SAFE_DELETE_ARRAY(name);
	SAFE_RELEASE(pTexture);
}

void CObjectFont::ResetStatus()
{
	D3DXMatrixIdentity(&matWorld);
	str = NULL;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	srcBlend = D3DBLEND_SRCALPHA;
	destBlend = D3DBLEND_INVSRCALPHA;
}

void CObjectFont::SetSize(int width, int height)
{
	t_width = width;
	t_height = height;
	c_width = width / (num_font >= 16 ? 16 : num_font);
	c_height = height / (num_font / 16);
}
