#ifndef MYMESH_H
#define MYMESH_H

#include <d3dx9.h>

struct SMeshFrame : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};

struct SMeshContainer : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9* ppTextures;
};

#endif