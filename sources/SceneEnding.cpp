#include "SceneEnding.h"
#include "SceneGameOver.h"

#include "Config.h"

CSceneEnding::CSceneEnding()
{
}

CSceneEnding::~CSceneEnding()
{
}

void CSceneEnding::Init(CSystemScene *_system)
{
	CSceneBase::Init(_system);
	// �e�O���t�B�b�N��ID�擾

	fontID = GetGraphics()->GetDrawObjectID("Data/Texture/font.png");

	// �e�ϐ��̏�����
	time = 0;

	GetMedia()->StopBGM();
}

void CSceneEnding::UnInit()
{
}

void CSceneEnding::Update()
{
	time++;

	// �v���C���[������L�[����������f�����I������
	if(GetInput(0, e_Config.key_ok) == 1)
	{
		MoveScene(new CSceneGameOver());
		return;
	}
	// ���ԂɂȂ�ƏI��
	if(time > 2400)
	{
		MoveScene(new CSceneGameOver());
		return;
	}
}

void CSceneEnding::Draw()
{
	D3DXMatrixTranslation(&mat, 50, (720-time/2), 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "Green beings can controll all of arms");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);
	
	D3DXMatrixTranslation(&mat, 50, (720-time/2)+48, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "Human being could not deal with it");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);

	D3DXMatrixTranslation(&mat, 50, (720-time/2)+48*2, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "At the end of war,");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);

	D3DXMatrixTranslation(&mat, 50, (720-time/2)+48*3, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "a lot of human being were died");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);
	
	D3DXMatrixTranslation(&mat, 50, (720-time/2)+48*4, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "a lot of stars were died");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);

	D3DXMatrixTranslation(&mat, 50, (720-time/2)+48*6, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "Space got GREEN");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);

	D3DXMatrixTranslation(&mat, 50, (720-time/2)+48*10, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "end");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);
}
