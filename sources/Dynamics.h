#ifndef DYNAMICS_H
#define DYNAMICS_H

#include <d3dx9.h>

#define DT_SPHERE	1
#define DT_LINE		2
#define DT_PLANE	3
#define DT_BOX		4

//=============================================================
// CDynamics
//-------------------------------------------------------------
// �S�Ẵ_�C�i�~�N�X(�Փ˔���)�̊��N���X�B
// �����蔻��̊�{�I�ȍ\�������肷��B
//=============================================================
class CDynamics
{
public:
	// �Փ˔���(�Q��)
	virtual bool Hit(CDynamics *target) = 0;
protected:
	// �_�C�i�~�N�X�̎��
	int dynamicsType;
public:
	int Type()
	{
		return dynamicsType;
	}
};

//=============================================================
// CBoundingSphere
//-------------------------------------------------------------
// ���̓����蔻������_�C�i�~�N�X�B
//=============================================================
class CBoundingSphere : public CDynamics
{
public:
	bool Hit(CDynamics *target);

	// ���S�_�x�N�g��
	D3DXVECTOR3 c;
	// ���a
	float r;

	// �R���X�g���N�^
	CBoundingSphere()
	{
		c.x = c.y = c.z = r = 0;
		dynamicsType = DT_SPHERE;
	}
};

//=============================================================
// CBoundingLine
//-------------------------------------------------------------
// �����̓����蔻������_�C�i�~�N�X�B
//=============================================================
class CBoundingLine : public CDynamics
{
public:
	bool Hit(CDynamics *target);

	// 2�_
	D3DXVECTOR3 a;
	D3DXVECTOR3 b;

	// �R���X�g���N�^
	CBoundingLine()
	{
		ZeroMemory(&a, sizeof(D3DXVECTOR3));
		ZeroMemory(&b, sizeof(D3DXVECTOR3));
		dynamicsType = DT_LINE;
	}
};

//=============================================================
// CBoundingPlane
//-------------------------------------------------------------
// ��̓����蔻������_�C�i�~�N�X�B
//=============================================================
class CBoundingPlane : public CDynamics
{
public:
	bool Hit(CDynamics *target);

	// ����A�����A�E���A�E��
	D3DXVECTOR3 lt, lb, rt, rb;

	// �R���X�g���N�^
	CBoundingPlane()
	{
		ZeroMemory(&lt, sizeof(D3DXVECTOR3));
		ZeroMemory(&lb, sizeof(D3DXVECTOR3));
		ZeroMemory(&rt, sizeof(D3DXVECTOR3));
		ZeroMemory(&rb, sizeof(D3DXVECTOR3));
		dynamicsType = DT_PLANE;
	}
};

//=============================================================
// CBoundingBox
//-------------------------------------------------------------
// �����`�̓����蔻������_�C�i�~�N�X�B
//=============================================================
class CBoundingBox : public CDynamics
{
public:
	bool Hit(CDynamics *target);

	// ��ʁA���
	CBoundingPlane t, b;

	// �R���X�g���N�^
	CBoundingBox()
	{
		dynamicsType = DT_BOX;
	}
};

#endif
