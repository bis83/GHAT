#ifndef TASKFACTORY_H
#define TASKFACTORY_H

#include "TaskManager.h"

#include "HandleSystem.h"

//=============================================================
// CTaskFactory
//-------------------------------------------------------------
// �e��^�X�N�𐶐�����H��N���X�B
//=============================================================
class CTaskFactory
{
public:
	CTaskFactory()
	{
	}
	~CTaskFactory()
	{
	}
	void Init(CHandleGraphics *_hGrap, CHandleMedia *_hMedi);

	// �A�C�e���̍쐬
	void CreateItem(D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);

	// ���e�̍쐬
	void CreateShot(int shotType, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);

	// �G�̍쐬
	void CreateEnemy(int enemyType, int enemyPattern, D3DXVECTOR3 vecPos);

	// �{�X�̍쐬
	void CreateBoss(int bossType);

	// �e�̍쐬
	void CreateBullet(int bulletType, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);

	// �����̍쐬
	void CreateExplode(int explodeType, D3DXVECTOR3 vecPos);

	// �A�C�e���擾���̃G�t�F�N�g�̍쐬
	void CreateItemGet(D3DXVECTOR3 vecPos);

	// �������̃G�t�F�N�g�쐬
	void CreateEquipEffect(D3DXVECTOR3 vecPos);

	// ��e���̃G�t�F�N�g�쐬
	void CreateHitEffect(D3DXVECTOR3 vecPos);

	// �~�T�C���̉��̍쐬
	void CreateMissileSmoke(D3DXVECTOR3 vecPos);

	// �w�i�̍쐬
	void CreateBack(int backType);

	// �n�`�̍쐬
	void CreateRig(int rigType, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);
private:
	// �O���t�B�b�N�X�ւ̃n���h��
	CHandleGraphics *hGrap;
	// ���f�B�A�ւ̃n���h��
	CHandleMedia *hMedi;
};

extern CTaskFactory e_taskFactory;

#endif
