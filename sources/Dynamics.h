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
// 全てのダイナミクス(衝突判定)の基底クラス。
// 当たり判定の基本的な構造を決定する。
//=============================================================
class CDynamics
{
public:
	// 衝突判定(参照)
	virtual bool Hit(CDynamics *target) = 0;
protected:
	// ダイナミクスの種類
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
// 球の当たり判定を持つダイナミクス。
//=============================================================
class CBoundingSphere : public CDynamics
{
public:
	bool Hit(CDynamics *target);

	// 中心点ベクトル
	D3DXVECTOR3 c;
	// 半径
	float r;

	// コンストラクタ
	CBoundingSphere()
	{
		c.x = c.y = c.z = r = 0;
		dynamicsType = DT_SPHERE;
	}
};

//=============================================================
// CBoundingLine
//-------------------------------------------------------------
// 線分の当たり判定を持つダイナミクス。
//=============================================================
class CBoundingLine : public CDynamics
{
public:
	bool Hit(CDynamics *target);

	// 2点
	D3DXVECTOR3 a;
	D3DXVECTOR3 b;

	// コンストラクタ
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
// 板状の当たり判定を持つダイナミクス。
//=============================================================
class CBoundingPlane : public CDynamics
{
public:
	bool Hit(CDynamics *target);

	// 左上、左下、右下、右上
	D3DXVECTOR3 lt, lb, rt, rb;

	// コンストラクタ
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
// 長方形の当たり判定を持つダイナミクス。
//=============================================================
class CBoundingBox : public CDynamics
{
public:
	bool Hit(CDynamics *target);

	// 上面、底面
	CBoundingPlane t, b;

	// コンストラクタ
	CBoundingBox()
	{
		dynamicsType = DT_BOX;
	}
};

#endif
