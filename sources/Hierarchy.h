#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <d3dx9.h>

class CHierarchy : public ID3DXAllocateHierarchy
{
public:
	CHierarchy();
	~CHierarchy();
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME*);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD*, LPD3DXSKININFO, LPD3DXMESHCONTAINER*);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
};

extern CHierarchy e_Hierarchy;

#endif