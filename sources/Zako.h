#ifndef ZAKO_H
#define ZAKO_H

#include "Enemy.h"

#include "Dynamics.h"

//=============================================================
// CZako1
//-------------------------------------------------------------
// 前方に弾を撃つザコ敵。
// pattern1 : 左に低速移動して(0)一定距離でピッチしながら画面中央方向右に折り返して(1)、再び左へ(2)
// pattern2 : 左から右に高速で移動したあと(0)、折り返して(1)弾を撃ちながら左へ(2)
// pattern3 : 弾を撃ちながら上下から画面中央方向左に向かい(0)、その後加速して左へ(1)
// pattern4 : 高速で左に移動しながら弾を撃つ(0)
//=============================================================
// 
class CZako1 : public CEnemy
{
public:
	CZako1(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action);
	~CZako1();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
	CDynamics* GetDynamics()
	{
		return &hit;
	}
private:
	void Shot(CHandleMedia *hMedi);
	int pattern;
	int act;
	D3DXVECTOR3 vecVel;

	int timer;
	CBoundingSphere hit;
	int shotSoundID;
};

//=============================================================
// CZako2
//-------------------------------------------------------------
// 4方向に弾を撃ちながら回転する敵。
// pattern1 : 画面中央方向に左右移動したあと(0)停止して弾を撃ち(1)、一定時間後自機方向に高速移動(2)
// pattern2 : 左右反対方向にに高速移動しながら弾を撃つ(0)
// pattern3 : 画面中央方向へ一定距離上下移動した後(0)、停止して弾を撃ち(1)、自機方向へ高速移動(2)
// pattern4 : 自機方向に高速移動した後(0)、一定距離まで接近すると停止して弾を撃ち(1)、右に高速移動(2)
//=============================================================
class CZako2 : public CEnemy
{
public:
	CZako2(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action);
	~CZako2();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
	CDynamics* GetDynamics()
	{
		return &hit;
	}
private:
	void Shot(CHandleMedia *hMedi);
	int pattern;
	int act;
	D3DXVECTOR3 vecVel;

	int timer;
	CBoundingSphere hit;
	int shotSoundID;
};

//=============================================================
// CZako3
//-------------------------------------------------------------
// ミサイルを発射する敵。
// pattern1 : 画面中央方向に一定距離左右移動した後(0)停止して弾を撃ち(1)、進行方向に加速して移動(2)
// pattern2 : 画面中央方向に一定距離上下移動した後(0)、低速でそのまま移動しながら弾を撃ち(1)そのまま画面外へ(2)
// pattern3 : 画面中央方向に一定距離左右移動した後(0)、自機依存の上下移動をしながら弾を撃ち(1)、左右方向に加速移動(2)
//=============================================================
class CZako3 : public CEnemy
{
public:
	CZako3(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action);
	~CZako3();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
	CDynamics* GetDynamics()
	{
		return &hit;
	}
private:
	void Shot(CHandleMedia *hMedi);
	int pattern;
	int act;
	D3DXVECTOR3 vecVel;

	int timer;
	CBoundingSphere hit;
	int shotSoundID;
};

//=============================================================
// CZako4
//-------------------------------------------------------------
// ミサイルとショットを併用する敵。
// pattern1 : 一定距離左右移動した後に(0)停止して弾を撃ち(1)、上下移動して画面外に(2)
// pattern2 : 一定距離上下移動した後に(0)停止して弾を撃ち(1)、自機方向に高速移動(2)
// pattern3 : 一定距離左右移動した後(0)、自機依存の上下移動しながら弾を撃ち(1)左右方向加速移動する(2)
//=============================================================
class CZako4 : public CEnemy
{
public:
	CZako4(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action);
	~CZako4();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
	CDynamics* GetDynamics()
	{
		return &hit;
	}
private:
	void Shot(CHandleMedia *hMedi);
	int pattern;
	int act;
	D3DXVECTOR3 vecVel;

	int timer;
	CBoundingSphere hit;
	int shotSoundID[2];
};

//=============================================================
// CZako5
//-------------------------------------------------------------
// 自機狙いの弾を発射する敵。
// pattern1 : 左右反対方向に低速移動しながら弾を撃つ(0)
// pattern2 : 上下反対方向に低速移動しながら弾を撃つ(0)
//=============================================================
class CZako5 : public CEnemy
{
public:
	CZako5(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action);
	~CZako5();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
	CDynamics* GetDynamics()
	{
		return &hit;
	}
private:
	D3DXVECTOR3 vecVel;

	int timer;
	CBoundingSphere hit;
	int shotSoundID;
};

//=============================================================
// CZako6
//-------------------------------------------------------------
// 3way弾を発射する敵。
// pattern1 : 左右方向に一定距離移動した後(0)、停止して弾を撃ち(1)、高速で反対方向に移動(2)
// pattern2 : 上下方向に低速移動しながら弾を撃つ(0)
//=============================================================
class CZako6 : public CEnemy
{
public:
	CZako6(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int  action);
	~CZako6();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
	CDynamics* GetDynamics()
	{
		return &hit;
	}
private:
	void Shot(CHandleMedia *hMedi);
	int pattern;
	int act;
	D3DXVECTOR3 vecVel;

	int timer;
	CBoundingSphere hit;
	int shotSoundID;
};

#endif
