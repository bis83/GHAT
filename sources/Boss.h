#ifndef BOSS_H
#define BOSS_H

#include "Thing.h"
#include "Dynamics.h"

//=============================================================
// CBoss
//-------------------------------------------------------------
// �{�X���N���X�B
//=============================================================
class CBoss : public CThingMesh
{
public:
	CBoss() {}
	virtual ~CBoss() {};
	
	virtual bool Update(CHandleMedia *hMedi) = 0;
	virtual bool Hit(CDynamics *target) = 0;
	virtual void Draw(CHandleGraphics *hGrap) = 0;
	void Damage(int d) {
		life -= d;
	}
protected:
	int life;
	int pattern;
	int act;
	int timer;
};

//=============================================================
// CBoss1
//-------------------------------------------------------------
// �X�e�[�W1,3�{�X�B
//-------------------------------------------------------------
// pattern1 : 3way�o���J��
// pattern2 : �~�T�C��
// pattern3 : zako2�ˏo
// pattern4 : ���@�_���o���J��+�~�T�C��
// pattern5 : zako6�o��
// pattern6 : �������C���_�[
// 1~6���J��Ԃ�(3�T�Ŏ���)
//=============================================================
class CBoss1 : public CBoss
{
public:
	CBoss1(CHandleGraphics *hGrap, CHandleMedia *hMedi);
	~CBoss1();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
private:
	CBoundingSphere hit[3];
	int loop;
	int shotSoundID[3];
};

//=============================================================
// CBoss2
//-------------------------------------------------------------
// �X�e�[�W2,4�{�X�B
// �X�e�[�W2�ł�覐΂���Q���Ƃ��ēo�ꂷ��B
//-------------------------------------------------------------
// pattern1 : �ړ��Ȃ�+�S����10way�e
// pattern2 : ���@�ˑ��c�ړ�+���@�_��7way
// pattern3 : �ړ��Ȃ�+zako1�o��
// pattern4 : ���@�ˑ��c�ړ�+4way�o���J��+�~�T�C��
// pattern5 : �ړ��Ȃ�+zako5�o��
// pattern6 : ���@�ˑ��c�ړ�+�������@�_���e+�S����10way
// pattern7 : �ړ��Ȃ�+zako2�ˏo
// pattern8 : ���@�ˑ��c�ړ�+���@�_������27way�e
// 1~8���J��Ԃ�(2�T�Ŏ���)
//=============================================================
class CBoss2 : public CBoss
{
public:
	CBoss2(CHandleGraphics *hGrap, CHandleMedia *hMedi);
	~CBoss2();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
private:
	CBoundingSphere hit[3];
	int loop;
	// �����e�[�u��
	char s_table[19];
	int s_index;
	int shotSoundID[3];
};

//=============================================================
// CBoss3
//-------------------------------------------------------------
// �X�e�[�W5�{�X�B
//-------------------------------------------------------------
// pattern1 : ���@�_��3way�e		���@�ˑ��㉺�ړ�
// pattern2 : zako1�o��				�ړ��Ȃ�
// pattern3 : ��ʃ~�T�C��			���@�����Ɉړ�
// pattern4 : zako2�o��				����x�����C���ɕ��s�ړ�
// pattern5 : �����_���o���J��		���@�ˑ��㉺�ړ�
// pattern6 : �S����10way+�Q�����e	�ړ��Ȃ�
// pattern7 : zako6�o��				�ړ��Ȃ�
// pattern8 : ���@�_������9way		���@�ˑ��㉺�ړ�
// pattern9 : �����U��+zako1�o��	��ʒ����Ɉړ�
// 1~8���J��Ԃ��A�̗�1/8�ȉ���pattern9�Ɉڍs
//=============================================================
class CBoss3 : public CBoss
{
public:
	CBoss3(CHandleGraphics *hGrap, CHandleMedia *hMedi);
	~CBoss3();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
private:
	CBoundingSphere hit[3];
	int loop;
	int shotSoundID[3];
};

#endif