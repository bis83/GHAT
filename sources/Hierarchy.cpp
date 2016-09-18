#include "Hierarchy.h"
#include "MyMesh.h"
#include "SafeRelease.h"

CHierarchy::CHierarchy()
{
}

CHierarchy::~CHierarchy()
{
}

// フレームの生成
HRESULT CHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame)
{
	SMeshFrame *pFrame;

	pFrame = new SMeshFrame();
	if(pFrame == NULL)
	{
		return E_OUTOFMEMORY;
	}
	pFrame->Name =  new TCHAR[lstrlen(Name)+1];
	if(!pFrame->Name)
	{
		return E_FAIL;
	}
	strcpy(pFrame->Name, Name);

	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
	pFrame->pMeshContainer = NULL;
	pFrame->pFrameFirstChild = NULL;
	pFrame->pFrameSibling = NULL;
	*ppNewFrame = pFrame;
	pFrame = NULL;
	delete pFrame;

	return S_OK;
}

// メッシュコンテナの生成
HRESULT CHierarchy::CreateMeshContainer(LPCTSTR Name, const D3DXMESHDATA *pMeshData, const D3DXMATERIAL *pMaterials,
										const D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials, const DWORD *pAdjacency,
										LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER *ppMeshContainer)
{
	HRESULT hr;
	SMeshContainer *pMeshContainer = NULL;
	INT iFacesAmount;
	INT iMaterial;
	LPDIRECT3DDEVICE9 pDevice = NULL;
	LPD3DXMESH pMesh = NULL;
	*ppMeshContainer = NULL;

	pMesh = pMeshData->pMesh;
	pMeshContainer = new SMeshContainer;
	if(pMeshContainer == NULL)
	{
		return E_OUTOFMEMORY;
	}
	ZeroMemory(pMeshContainer, sizeof(SMeshContainer));
	pMeshContainer->Name = new TCHAR[lstrlen(Name)+1];
	if(!pMeshContainer->Name)
	{
		return E_FAIL;
	}
	strcpy(pMeshContainer->Name, Name);
	pMesh->GetDevice(&pDevice);
	iFacesAmount = pMesh->GetNumFaces();
	
	if(!(pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		hr = pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF() | D3DFVF_NORMAL, pDevice, &pMeshContainer->MeshData.pMesh);
		if(FAILED(hr))
		{
			return E_FAIL;
		}
		pMesh = pMeshContainer->MeshData.pMesh;
		D3DXComputeNormals(pMesh, NULL);
	} else {
		pMeshContainer->MeshData.pMesh = pMesh;
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		pMesh->AddRef();
	}
	pMeshContainer->NumMaterials = max(1, NumMaterials);
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	pMeshContainer->pAdjacency = new DWORD[iFacesAmount*3];
	if((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
	{
		return E_OUTOFMEMORY;
	}
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD)*iFacesAmount*3);
	memcpy(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9)*pMeshContainer->NumMaterials);
	if(NumMaterials > 0)
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL)*NumMaterials);
		for(iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
		{
			if(pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
			{
				TCHAR strTexturePath[MAX_PATH];
				strcpy(strTexturePath, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
				if(FAILED(D3DXCreateTextureFromFile(pDevice, strTexturePath, &pMeshContainer->ppTextures[iMaterial])))
				{
					pMeshContainer->ppTextures[iMaterial] = NULL;
				}
				pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
			} else {
				pMeshContainer->pMaterials[0].pTextureFilename = NULL;
				memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
				pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
				pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
				pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
				pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
			}
		}
		*ppMeshContainer = pMeshContainer;
		pMeshContainer = NULL;
		if(pMeshContainer != NULL)
		{
			DestroyMeshContainer(pMeshContainer);
		}
	}
	return S_OK;
}
// フレームの破棄
HRESULT CHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	SAFE_DELETE_ARRAY(pFrameToFree->Name);
	SAFE_DELETE(pFrameToFree);
	return S_OK;
}
// メッシュコンテナの破棄
HRESULT CHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	INT iMaterial;
	SMeshContainer *pMeshContainer = (SMeshContainer*)pMeshContainerBase;

	SAFE_DELETE_ARRAY(pMeshContainer->Name);
	SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
	SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);

	if(pMeshContainer->ppTextures != NULL)
	{
		for(iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			SAFE_RELEASE(pMeshContainer->ppTextures[iMaterial]);
		}
	}

	SAFE_DELETE_ARRAY(pMeshContainer->ppTextures);
	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);

	SAFE_DELETE(pMeshContainer);
	return S_OK;
}

CHierarchy e_Hierarchy;
