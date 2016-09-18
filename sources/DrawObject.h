#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <d3dx9.h>

// �`��I�u�W�F�N�g�^�C�v
#define DOT_MESH		1
#define DOT_SPRITE		2
#define DOT_FONT		3
#define DOT_ANIMESH		4

// �`��I�u�W�F�N�g�X�e�[�^�X
typedef enum _DOSTATUS {
	DOS_MATRIX = 1,
	DOS_SRCBLEND = 2,
	DOS_DESTBLEND = 3,
	DOS_BILLBOARD = 4,
	DOS_CULL = 5,
	DOS_SHADE = 6,
	DOS_FILL = 7,
	DOS_EFFECT = 8,
	DOS_COLOR = 9,
	DOS_SIZE = 10,
	DOS_STRING = 11,
} DOSTATUS;

//=============================================================
// CDrawObject
//-------------------------------------------------------------
// �`��I�u�W�F�N�g�B�S�ẴI�u�W�F�N�g�̊��N���X�B
// ���O�ƃI�u�W�F�N�g�̎�ނ��Ǘ�����B
//=============================================================
class CDrawObject
{
public:
	// ����
	virtual void Create(const char* filename, LPDIRECT3DDEVICE9 pDevice) = 0;
	// �j��
	virtual void Destroy() = 0;
	// �I�u�W�F�N�g�^�C�v�̎擾
	int GetObjectType() { return objectType; }
	// ���O�̎擾
	LPSTR GetName() { return name; }
protected:
	int objectType;
	LPSTR name;
};

//=============================================================
// CObjectMesh
//-------------------------------------------------------------
// ���b�V���I�u�W�F�N�g�B
// �A�j���[�V�������b�V�����T�|�[�g����B
//=============================================================
class CObjectMesh : public CDrawObject
{
public:
	// ����
	void Create(const char* filename, LPDIRECT3DDEVICE9 pDevice);
	void Destroy();

	void ResetStatus();

	// �t���[�����[�g
	LPD3DXFRAME pFrameRoot;
	// ���b�V��
	LPD3DXMESH pMesh;
	// �A�j���R���g���[���[
	LPD3DXANIMATIONCONTROLLER pAnimeController;
	// ���b�V���}�e���A��
	D3DMATERIAL9* pMeshMaterials;
	// ���b�V���e�N�X�`��
	LPDIRECT3DTEXTURE9* pMeshTextures;
	// �}�e���A������
	DWORD dwNumMaterials;

	// ���[���h�s��
	D3DXMATRIXA16 matWorld;
	// �u�����h�^�C�v
	D3DBLEND srcBlend;
	D3DBLEND destBlend;
	// �r���{�[�f�B���O
	BOOL billboarding;
	// �J�����O
	D3DCULL cullMode;
	// �V�F�[�f�B���O���[�h
	D3DSHADEMODE shadeMode;
	// �t�B�����[�h
	D3DFILLMODE fillMode;
	// �v���O���u���V�F�[�f�B���O(������)
	int effectID;
};

//=============================================================
// CObjectSprite
//-------------------------------------------------------------
// �X�v���C�g�p�I�u�W�F�N�g�B
// �e�N�X�`���ƃX�v���C�g�̑傫���ƐF�����B
//=============================================================
class CObjectSprite : public CDrawObject
{
public:
	void Create(const char* filename, LPDIRECT3DDEVICE9 pDevice);
	void Destroy();

	// �T�C�Y�̃Z�b�g
	void SetSize(int width, int height);

	void ResetStatus();

	// �e�N�X�`��
	LPDIRECT3DTEXTURE9 pTexture;
	// ���S�_
	D3DXVECTOR3 vecCenter;
	// ��`
	RECT rect;

	// ���[���h�s��
	D3DXMATRIXA16 matWorld;
	// �F
	D3DCOLOR color;
	// �u�����h�^�C�v
	D3DBLEND srcBlend;
	D3DBLEND destBlend;
	// �r���{�[�h
	BOOL billboarding;
};

//=============================================================
// CObjectFont
//-------------------------------------------------------------
// �t�H���g�p�X�v���C�g�I�u�W�F�N�g�B
// �t�H���g�̃e�N�X�`���摜�ƕ���������B
//=============================================================
class CObjectFont : public CDrawObject
{
public:
	void Create(const char* filename, LPDIRECT3DDEVICE9 pDevice);
	void Destroy();

	void SetSize(int width, int height);

	void ResetStatus();

	// �e�N�X�`��
	LPDIRECT3DTEXTURE9 pTexture;
	// ��`
	RECT rect;
	// �e�N�X�`���S�̂̑傫��
	int t_width, t_height;
	// �t�H���g�̎��
	int num_font;
	// �ꕶ���̑傫��
	int c_width, c_height;
	// �����̕ϊ��p�z��
	char c[256];

	// ������
	LPSTR str;
	// ���[���h�s��
	D3DXMATRIXA16 matWorld;
	// �F
	D3DCOLOR color;
	// �u�����h�^�C�v
	D3DBLEND srcBlend;
	D3DBLEND destBlend;
};

#endif
