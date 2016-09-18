#ifndef ZAKO_H
#define ZAKO_H

#include "Enemy.h"

#include "Dynamics.h"

//=============================================================
// CZako1
//-------------------------------------------------------------
// �O���ɒe�����U�R�G�B
// pattern1 : ���ɒᑬ�ړ�����(0)��苗���Ńs�b�`���Ȃ����ʒ��������E�ɐ܂�Ԃ���(1)�A�Ăэ���(2)
// pattern2 : ������E�ɍ����ňړ���������(0)�A�܂�Ԃ���(1)�e�������Ȃ��獶��(2)
// pattern3 : �e�������Ȃ���㉺�����ʒ����������Ɍ�����(0)�A���̌�������č���(1)
// pattern4 : �����ō��Ɉړ����Ȃ���e������(0)
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
// 4�����ɒe�������Ȃ����]����G�B
// pattern1 : ��ʒ��������ɍ��E�ړ���������(0)��~���Ēe������(1)�A��莞�Ԍ㎩�@�����ɍ����ړ�(2)
// pattern2 : ���E���Ε����ɂɍ����ړ����Ȃ���e������(0)
// pattern3 : ��ʒ��������ֈ�苗���㉺�ړ�������(0)�A��~���Ēe������(1)�A���@�����֍����ړ�(2)
// pattern4 : ���@�����ɍ����ړ�������(0)�A��苗���܂Őڋ߂���ƒ�~���Ēe������(1)�A�E�ɍ����ړ�(2)
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
// �~�T�C���𔭎˂���G�B
// pattern1 : ��ʒ��������Ɉ�苗�����E�ړ�������(0)��~���Ēe������(1)�A�i�s�����ɉ������Ĉړ�(2)
// pattern2 : ��ʒ��������Ɉ�苗���㉺�ړ�������(0)�A�ᑬ�ł��̂܂܈ړ����Ȃ���e������(1)���̂܂܉�ʊO��(2)
// pattern3 : ��ʒ��������Ɉ�苗�����E�ړ�������(0)�A���@�ˑ��̏㉺�ړ������Ȃ���e������(1)�A���E�����ɉ����ړ�(2)
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
// �~�T�C���ƃV���b�g�𕹗p����G�B
// pattern1 : ��苗�����E�ړ��������(0)��~���Ēe������(1)�A�㉺�ړ����ĉ�ʊO��(2)
// pattern2 : ��苗���㉺�ړ��������(0)��~���Ēe������(1)�A���@�����ɍ����ړ�(2)
// pattern3 : ��苗�����E�ړ�������(0)�A���@�ˑ��̏㉺�ړ����Ȃ���e������(1)���E���������ړ�����(2)
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
// ���@�_���̒e�𔭎˂���G�B
// pattern1 : ���E���Ε����ɒᑬ�ړ����Ȃ���e������(0)
// pattern2 : �㉺���Ε����ɒᑬ�ړ����Ȃ���e������(0)
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
// 3way�e�𔭎˂���G�B
// pattern1 : ���E�����Ɉ�苗���ړ�������(0)�A��~���Ēe������(1)�A�����Ŕ��Ε����Ɉړ�(2)
// pattern2 : �㉺�����ɒᑬ�ړ����Ȃ���e������(0)
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
