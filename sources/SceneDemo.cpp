#include "SceneDemo.h"
#include "SceneTitle.h"
#include "Config.h"

CSceneDemo::CSceneDemo()
{
}

CSceneDemo::~CSceneDemo()
{
}

void CSceneDemo::Init(CSystemScene *_system)
{
	CSceneBase::Init(_system);
	// 各グラフィックのID取得
	starID = GetGraphics()->GetDrawObjectID("Data/Texture/particle.png");

	fontID = GetGraphics()->GetDrawObjectID("Data/Texture/font.png");

	bill = TRUE;

	srand(timeGetTime());
	for(int i=0; i<32; i++)
	{
		vecParticlePos[i].x = 2.0f - 0.04f*(rand()%100);
		vecParticlePos[i].y = 2.0f - 0.04f*(rand()%100);
		particleScaling[i] = 1.0f;
	}

	// 各変数の初期化
	time = 0;
}

void CSceneDemo::UnInit()
{
}

void CSceneDemo::Update()
{
	time++;
	// 背景パーティクルの移動
	for(int i=0; i<32; i++)
	{
		if(vecParticlePos[i].x > 0) {
			vecParticlePos[i].x += 0.01f;
			if(vecParticlePos[i].x > 3.0f)
			{
				vecParticlePos[i].x -= 2.49f;
			}
		} else {
			vecParticlePos[i].x -= 0.01f;
			if(vecParticlePos[i].x < -3.0f)
			{
				vecParticlePos[i].x += 2.49f;
			}
		}
		if(vecParticlePos[i].y > 0) {
			vecParticlePos[i].y += 0.01f;
			if(vecParticlePos[i].y > 3.0f)
			{
				vecParticlePos[i].y -= 2.49f;
			}
		} else {
			vecParticlePos[i].y -= 0.01f;
			if(vecParticlePos[i].y < -3.0f)
			{
				vecParticlePos[i].y += 2.49f;
			}
		}
		particleScaling[i] = 0.1f*sqrt(vecParticlePos[i].x*vecParticlePos[i].x+vecParticlePos[i].y*vecParticlePos[i].y);
	}

	// プレイヤーが決定キーを押したらデモを終了する
	if(GetInput(0, e_Config.key_ok) == 1)
	{
		MoveScene(new CSceneTitle());
		return;
	}
	// 時間になると終了
	if(time > 1980)
	{
		MoveScene(new CSceneTitle());
		return;
	}
}

void CSceneDemo::Draw()
{
	for(int i=0; i<32-(time/60); i++)
	{
		D3DXMatrixScaling(&mat2, particleScaling[i], particleScaling[i], 0);
		D3DXMatrixTranslation(&mat, vecParticlePos[i].x, vecParticlePos[i].y, 1);
		D3DXMatrixMultiply(&mat, &mat2, &mat);
		blend = D3DBLEND_ONE;
		color = D3DCOLOR_ARGB(255, 168, 255, 192);
		GetGraphics()->SetDrawObjectStatus(starID, DOS_SRCBLEND, &blend);
		GetGraphics()->SetDrawObjectStatus(starID, DOS_DESTBLEND, &blend);
		GetGraphics()->SetDrawObjectStatus(starID, DOS_COLOR, &color);
		GetGraphics()->SetDrawObjectStatus(starID, DOS_BILLBOARD, &bill);
		GetGraphics()->SetDrawObjectStatus(starID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(starID);
	}

	D3DXMatrixTranslation(&mat, 50, (720-time/2), 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "In 20XX");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);
	
	D3DXMatrixTranslation(&mat, 50, (720-time/2)+48, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "Human beings could travel between stars");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);

	D3DXMatrixTranslation(&mat, 50, (720-time/2)+48*2, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "They discovered countless green beings");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);

	D3DXMatrixTranslation(&mat, 50, (720-time/2)+48*3, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "at the end of space.");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);
	
	D3DXMatrixTranslation(&mat, 50, (720-time/2)+48*4, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	sprintf(string, "It was beginning of big war");
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);
}
