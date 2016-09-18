#include "SceneMain.h"
#include "SceneGameOver.h"
#include "SceneEnding.h"
#include "SafeRelease.h"

#include "Config.h"
#include "Ranking.h"
#include "MyShip.h"
#include "TaskManager.h"
#include "TaskFactory.h"

#include "Back.h"
#include "MyShip.h"
#include "Item.h"
#include "Bullet.h"
#include "Shot.h"
#include "Effect.h"
#include "Enemy.h"
#include "Rig.h"

CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

void CSceneMain::Init(CSystemScene *_system)
{
	CSceneBase::Init(_system);
	fontID = GetGraphics()->GetDrawObjectID("Data/Texture/font.png");
	pause_f = false;

	itemGetID = GetMedia()->GetMediaObjectID("Data/Media/item.wav");

	// ���@�̏�����
	e_MyShip.Init(GetGraphics());

	// �^�X�N�}�l�[�W���[�̏�����
	e_taskMgr.Init();
	e_taskFactory.Init(GetGraphics(), GetMedia());

	GetMedia()->SetPlayStatus(GetMedia()->GetMediaObjectID("Data/Media/airf.wav"), MOS_VOLUME, &e_Config.bgm_volume);
	GetMedia()->PlayBGM(GetMedia()->GetMediaObjectID("Data/Media/airf.wav"));

	wait = 0;
	gameover = false;

	script.Set("Data/Text/Stage1.txt");
}

void CSceneMain::UnInit()
{
}

void CSceneMain::Update()
{
	// �|�[�Y����
	if(GetInput(0, e_Config.key_pause) == 1)
	{
		// �|�[�Y�����̓���؂�
		pause_f = pause_f ? false : true;
		if(pause_f)
		{
			// BGM�̒�~
			GetMedia()->StopBGM();
		} else {
			// BGM�̍ĊJ
			GetMedia()->RestartBGM();
		}
	}
	// �|�[�Y���͏����𒆒f
	if(pause_f)
	{
		return;
	}

	// �X�e�[�W�X�N���v�g�̐i�s
	if(!script.Update())
	{
		MoveScene(new CSceneEnding());
		return;
	}

	// �Q�[���I�[�o�[����
	if(wait > 0)
	{
		wait--;
	} else {
		if(gameover)
		{
			MoveScene(new CSceneGameOver());
			return;
		}
		// ���@�����S�����ꍇ
		if(!e_MyShip.Revive())
		{
			wait = 60;
			gameover = true;
		}
	}

	// �ړ��Ǝ��S

	// �w�i�̈ړ�
	for(CTaskIter i(e_taskMgr.back); i.HasNext(); (((CBack*)i.Next())->Update() ? 1 : i.Remove()));
	// �A�C�e���̈ړ�
	for(CTaskIter i(e_taskMgr.item); i.HasNext(); (((CItem*)i.Next())->Update() ? 1 : i.Remove()));
	// ���@�̈ړ�
	e_MyShip.Update(GetInput(0, e_Config.key_shot), GetInput(0, e_Config.key_bomb),
		GetInput(0, ANALOG_X), GetInput(0, ANALOG_Y), GetMedia());
	// �G�̈ړ�
	for(CTaskIter i(e_taskMgr.enemy); i.HasNext(); (((CEnemy*)i.Next())->Update(GetMedia()) ? 1 : i.Remove()));
	if(e_taskMgr.boss != NULL)
	{
		if(!e_taskMgr.boss->Update(GetMedia()))
		{
			SAFE_DELETE(e_taskMgr.boss);
			script.BossEnd();
		}
	}
	// �V���b�g�̈ړ�
	for(CTaskIter i(e_taskMgr.shot); i.HasNext(); (((CShot*)i.Next())->Update() ? 1 : i.Remove()));
	// �G�e�̈ړ�
	for(CTaskIter i(e_taskMgr.bullet); i.HasNext(); (((CBullet*)i.Next())->Update() ? 1 : i.Remove()));
	// �n�`�̈ړ�
	for(CTaskIter i(e_taskMgr.rig); i.HasNext(); (((CRig*)i.Next())->Update() ? 1 : i.Remove()));
	
	// �G�t�F�N�g�̈ړ�
	for(CTaskIter i(e_taskMgr.effect); i.HasNext(); (((CEffect*)i.Next())->Update() ? 1 : i.Remove()));

	// ���@�̓����蔻��
	CTaskBase *t, *k;
	if(!e_MyShip.Blink())
	{
		// ���@�ƓG
		for(CTaskIter i(e_taskMgr.enemy); i.HasNext();)
		{
			t = i.Next();
			if(((CEnemy*)t)->Hit(&e_MyShip.hitRange))
			{
				((CEnemy*)t)->Damage(1);
				e_MyShip.Dead();
			}
		}
		// ���@�ƃ{�X
		if(e_taskMgr.boss != NULL)
		{
			if(e_taskMgr.boss->Hit(&e_MyShip.hitRange))
			{
				e_taskMgr.boss->Damage(1);
				e_MyShip.Dead();
			}
		}
		// ���@�ƓG�e
		for(CTaskIter i(e_taskMgr.bullet); i.HasNext();)
		{
			t = i.Next();
			if(((CBullet*)t)->Hit(&e_MyShip.hitRange))
			{
				((CBullet*)t)->Dead();
				e_MyShip.Dead();
			}
		}
		// ���@�ƒn�`
		for(CTaskIter i(e_taskMgr.rig); i.HasNext();)
		{
			t = i.Next();
			if(((CRig*)t)->Hit(&e_MyShip.hitRange))
			{
				((CRig*)t)->Damage(1);
				if(((CRig*)t)->Power() > 0)
				{
					e_MyShip.Dead();
				}
			}
		}
	}
	// ���@�ƃA�C�e��
	for(CTaskIter i(e_taskMgr.item); i.HasNext();)
	{
		t = i.Next();
		// �A�C�e�����������ꍇ
		if(((CItem*)t)->Hit(&e_MyShip.hitRange))
		{
			e_taskFactory.CreateItemGet(((CItem*)t)->vecPos);
			e_MyShip.AddScore(100);
			((CItem*)t)->Dead();
			continue;
		}
		// �A�C�e������͈͓��ɓ������ꍇ
		if(((CItem*)t)->Hit(&e_MyShip.itemCollectRange))
		{
			((CItem*)t)->Gather();
			continue;
		}
	}

	// �V���b�g�ƓG
	for(CTaskIter i(e_taskMgr.shot); i.HasNext();)
	{
		t = i.Next();
		for(CTaskIter j(e_taskMgr.enemy); j.HasNext();)
		{
			k = j.Next();
			// �ڐG���Ă���ꍇ�̓V���b�g���E���G�̗̑͂����炷
			if(((CShot*)t)->Hit(((CEnemy*)k)->GetDynamics()))
			{
				e_taskFactory.CreateHitEffect((((CEnemy*)k)->vecPos+((CShot*)t)->vecPos)/2);
				((CShot*)t)->Dead();
				((CEnemy*)k)->Damage(((CShot*)t)->Power());
				if(((CShot*)t)->ShotType() == 0)
				{
					// �G��̍U���Ŏ��S�����ꍇ�͕�����v���C���[���擾����
					if(((CEnemy*)k)->IsDead())
					{
						e_MyShip.GainWeapon(((CEnemy*)k)->GetEnemyID());
						// �G��̍U���̏ꍇ�͓��_�A�C�e�����o��������
						for(int i=0; i<e_Config.difficult; i++)
						{
							e_taskFactory.CreateItem(((CEnemy*)k)->vecPos,
								D3DXVECTOR3(0.01f*cos((float)timeGetTime()+i*2),
								0.01f*sin((float)timeGetTime()+i*2), 0.0f));
						}
					}

				} else {
					// �������ݓ_����ɓ����
					e_MyShip.AddScore(20);
				}
			}
		}
		// �V���b�g�ƃ{�X
		if(e_taskMgr.boss != NULL)
		{
			if(e_taskMgr.boss->Hit(((CShot*)t)->GetDynamics()))
			{
				e_taskFactory.CreateHitEffect((e_taskMgr.boss->vecPos+((CShot*)t)->vecPos)/2);
				((CShot*)t)->Dead();
				e_taskMgr.boss->Damage(((CShot*)t)->Power());
				if(((CShot*)t)->ShotType() == 0)
				{
					// �G��̍U���̏ꍇ�͓��_�A�C�e�����o��������
					for(int i=0; i<e_Config.difficult; i++)
					{
						e_taskFactory.CreateItem(e_taskMgr.boss->vecPos,
							D3DXVECTOR3(0.01f*cos((float)timeGetTime()+i*2),
							0.01f*sin((float)timeGetTime()+i*2), 0.0f));
					}
				} else {
					// �������ݓ_����ɓ����
					e_MyShip.AddScore(20);
				}
			}
		}
	}
	// �V���b�g�ƒn�`
	for(CTaskIter i(e_taskMgr.shot); i.HasNext();)
	{
		t = i.Next();
		for(CTaskIter j(e_taskMgr.rig); j.HasNext();)
		{
			k = j.Next();
			// �ڐG���Ă���ꍇ�̓V���b�g���E���G�̗̑͂����炷
			if(((CShot*)t)->Hit(((CRig*)k)->GetDynamics()))
			{
				e_taskFactory.CreateHitEffect((((CRig*)k)->vecPos+((CShot*)t)->vecPos)/2);
				((CShot*)t)->Dead();
				((CRig*)k)->Damage(((CShot*)t)->Power());
				if(((CShot*)t)->ShotType() == 0)
				{
				} else {
					// �������ݓ_����ɓ����
					e_MyShip.AddScore(20);
				}
			}
		}
	}
	// �G�e�ƒn�`
	for(CTaskIter i(e_taskMgr.bullet); i.HasNext();)
	{
		t = i.Next();
		for(CTaskIter j(e_taskMgr.rig); j.HasNext();)
		{
			k = j.Next();
			// �ڐG���Ă���ꍇ�̓V���b�g���E���G�̗̑͂����炷
			if(((CBullet*)t)->Hit(((CRig*)k)->GetDynamics()))
			{
				e_taskFactory.CreateHitEffect((((CRig*)k)->vecPos+((CBullet*)t)->vecPos)/2);
				((CBullet*)t)->Dead();
				((CRig*)k)->Damage(1);
			}
		}
	}
}

void CSceneMain::Draw()
{
	// �w�i�̕`��
	for(CTaskIter i(e_taskMgr.back); i.HasNext(); ((CBack*)i.Next())->Draw(GetGraphics()));
	// �A�C�e���̕`��
	for(CTaskIter i(e_taskMgr.item); i.HasNext(); ((CItem*)i.Next())->Draw(GetGraphics()));
	// �V���b�g�̕`��
	for(CTaskIter i(e_taskMgr.shot); i.HasNext(); ((CBullet*)i.Next())->Draw(GetGraphics()));
	// �G�e�̕`��
	for(CTaskIter i(e_taskMgr.bullet); i.HasNext(); ((CBullet*)i.Next())->Draw(GetGraphics()));
	// ���@�̕`��
	e_MyShip.Draw(GetGraphics());
	// �G�@�̕`��
	for(CTaskIter i(e_taskMgr.enemy); i.HasNext(); ((CEnemy*)i.Next())->Draw(GetGraphics()));
	if(e_taskMgr.boss != NULL)
	{
		e_taskMgr.boss->Draw(GetGraphics());
	}

	// �n�`�̕`��
	for(CTaskIter i(e_taskMgr.rig); i.HasNext(); ((CRig*)i.Next())->Draw(GetGraphics()));

	// �G�t�F�N�g�̕`��
	for(CTaskIter i(e_taskMgr.effect); i.HasNext(); ((CEffect*)i.Next())->Draw(GetGraphics()));

	// �X�e�[�^�X(�X�R�A�Ǝc�@)�̕`��
	sprintf(string, "Rest %1d  Score %8d", e_MyShip.GetRest(), e_MyShip.GetScore());
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	D3DXMatrixTranslation(&mat, 360, 0, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	GetGraphics()->DrawObject(fontID);
	// �c�e�̕\��
	if(e_MyShip.Equipping())
	{
		sprintf(string, "Type%1d  Bullet%3d", e_MyShip.GetWeaponID(), e_MyShip.GetBullet());
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		D3DXMatrixTranslation(&mat, 24, 678, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(fontID);
	} else {
		// �`���[�W���̕\��
		sprintf(string, "Charge %3d", e_MyShip.GetCharge());
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		D3DXMatrixTranslation(&mat, 24, 678, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(fontID);
	}

	// FPS�̕`��
	sprintf(string, "FPS_%2d", GetFPS());
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);

	// �|�[�Y�̕`��
	if(pause_f)
	{
		sprintf(string, "Pause");
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		D3DXMatrixTranslation(&mat, 580, 336, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(fontID);
	}
}
