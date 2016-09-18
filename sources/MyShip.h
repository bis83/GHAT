#ifndef MYSHIP_H
#define MYSHIP_H

#include "Thing.h"
#include "Dynamics.h"

//=============================================================
// CMyShip
//-------------------------------------------------------------
// ���@�̏������N���X�B
// �Q�[�����ɂ͈�̂������݂��Ȃ��̂œ��ʂȃN���X�Ƃ��ėp�ӂ���B
//=============================================================
class CMyShip : public CThingMesh
{
public:
	CMyShip();
	// ������(���C���V�[���J�n���̃Z�b�g�A�b�v)
	void Init(CHandleGraphics* hGrap);
	// �X�V
	void Update(int a, int b, int anaX, int anaY, CHandleMedia *hMedi);
	// �`��
	void Draw(CHandleGraphics* hGrap);
	// �o��
	bool Revive();
	// �c�@�̎擾
	int GetRest();
	// �X�R�A�̎擾
	int GetScore();
	// �X�R�A�̉��Z
	void AddScore(int pt);
	// ���S
	void Dead();
	// �E�F�|���擾
	void GainWeapon(int wn);

	// �����蔻��
	CBoundingSphere hitRange;
	// �A�C�e���̉���͈�
	CBoundingSphere itemCollectRange;
	bool Blink()
	{
		return blink ? true : false;
	}
	bool Gather()
	{
		return gathering;
	}
	int GetBullet() 
	{
		return restShot;
	}
	bool Equipping()
	{
		return weaponID ? true : false;
	}
	int GetWeaponID()
	{
		return weaponID;
	}
	int GetCharge()
	{
		return min(t_charge * 100 / 30, 100);
	}
private:
	// �V���b�g
	void Shot(int shotNumber);

	// �X�R�A
	int score;
	// �c�@
	int restShip;
	// ���G����
	int blink;
	// ���@�̎��
	int shipType;
	// ���ݏ������Ă��镐��^�C�v
	int weaponID;
	// �G��`���[�W�����t���O
	bool tentacle;
	int t_charge;
	// �c�e��
	int restShot;
	// ���S����
	bool dead;
	// �������
	bool gathering;
	int g_charge;

	// �ŏI�ړ����W�A���p
	float lastMoveRad;

	// ����O���t�B�b�NID
	int weaponGrapID[8];
};

extern CMyShip e_MyShip;

#endif