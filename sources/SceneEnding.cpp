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
	// 各グラフィックのID取得

	fontID = GetGraphics()->GetDrawObjectID("Data/Texture/font.png");

	// 各変数の初期化
	time = 0;

	GetMedia()->StopBGM();
}

void CSceneEnding::UnInit()
{
}

void CSceneEnding::Update()
{
	time++;

	// プレイヤーが決定キーを押したらデモを終了する
	if(GetInput(0, e_Config.key_ok) == 1)
	{
		MoveScene(new CSceneGameOver());
		return;
	}
	// 時間になると終了
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
