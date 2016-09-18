#include "SceneGameOver.h"

#include "Config.h"
#include "Ranking.h"

#include "SceneDemo.h"
#include "MyShip.h"

#include <iostream>
#include <fstream>

using namespace std;

CSceneGameOver::CSceneGameOver()
{
}

CSceneGameOver::~CSceneGameOver()
{
}

void CSceneGameOver::Init(CSystemScene *_system)
{
	CSceneBase::Init(_system);

	// 各IDの取得
	fontID = GetGraphics()->GetDrawObjectID("Data/Texture/font.png");

	planetID = GetGraphics()->GetDrawObjectID("Data/Mesh/bluePlanet.x");
	fill = D3DFILL_WIREFRAME;

	overID = GetGraphics()->GetDrawObjectID("Data/Texture/gameover.png");

	cursorID = GetMedia()->GetMediaObjectID("Data/Media/cursor.wav");
	decideID = GetMedia()->GetMediaObjectID("Data/Media/decide.wav");
	cancelID = GetMedia()->GetMediaObjectID("Data/Media/cancel.wav");
	overSeID = GetMedia()->GetMediaObjectID("Data/Media/over.wav");
	entryBgmID = GetMedia()->GetMediaObjectID("Data/Media/loop2.wav");

	phase = 0;
	wait = 60;

	score = e_MyShip.GetScore();
	name[0] = name[1] = name[2] = '_';
	name[3] = '\0';
	rank = 5;
	nameIndex = 0;
	index = 1;

	ifstream fin("Data/Text/Font.txt");
	for(int i=0; i<64; i++)
	{
		charTable[i] = 0;
	}
	char temp[16+1];
	while(!fin.eof())
	{
		fin >> temp;
		strcat(charTable, temp);
	}
	fin.close();

	GetMedia()->StopBGM();
	GetMedia()->SetPlayStatus(overSeID, MOS_VOLUME, &e_Config.se_volume);
	GetMedia()->PlaySE(overSeID);
}

void CSceneGameOver::UnInit()
{
}

void CSceneGameOver::Draw()
{
	char str[16];
	switch(phase)
	{
	case 0:
		D3DXMatrixTranslation(&mat, 640, 360, 0);
		GetGraphics()->SetDrawObjectStatus(overID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(overID);
		break;
	case 1:
		GetGraphics()->SetDrawObjectStatus(planetID, DOS_FILL, &fill);
		D3DXMatrixRotationY(&mat, timeGetTime() * D3DX_PI / 360 / 12);
		GetGraphics()->SetDrawObjectStatus(planetID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(planetID);
		// 文字テーブルの描画
		for(int i=0; i<64; i++)
		{
			D3DXMatrixTranslation(&mat, 448+24*(i%16), 422+48*(i/16), 0);
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
			color = ((i == index) ? D3DCOLOR_ARGB(255, 255, 255, 255) : D3DCOLOR_ARGB(128, 255, 255, 255));
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
			str[0] = charTable[i];
			str[1] = '\0';
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, str);
			GetGraphics()->DrawObject(fontID);
		}
		// ランクの描画
		D3DXMatrixTranslation(&mat, 400, 96, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		sprintf(str, "%1d", rank+1);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, str);
		GetGraphics()->DrawObject(fontID);
		// 名前の描画
		D3DXMatrixTranslation(&mat, 400+24*5, 96, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, name);
		GetGraphics()->DrawObject(fontID);
		// スコアの描画
		D3DXMatrixTranslation(&mat, 400+24*12, 96, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		sprintf(str, "%8d", score);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, str);
		GetGraphics()->DrawObject(fontID);
		break;
	}
}

void CSceneGameOver::Update()
{
	if(wait > 0)
	{
		wait--;
		return;
	}
	switch(phase)
	{
	case 0:		// ゲームオーバー
		if(GetInput(0, e_Config.key_ok))
		{
			for(int i=0; i<5; i++)
			{
				if(score > e_Ranking.score[i])
				{
					rank = i;
					break;
				}
			}
			if(rank < 5)
			{
				GetMedia()->StopSE();
				GetMedia()->SetPlayStatus(entryBgmID, MOS_VOLUME, &e_Config.bgm_volume);
				GetMedia()->PlayBGM(entryBgmID);
				phase++;
				wait = 10;
			} else {
				phase += 2;
			}
		}
		break;
	case 1:		// ネームエントリー
		if(GetInput(0, ANALOG_X) > 500)
		{
			if(nameIndex > 2)
			{
				return;
			}
			GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(cursorID);
			index++;
			if(index > 62)
			{
				index = 1;
			}
			wait = 6;
			break;
		}
		if(GetInput(0, ANALOG_X) < -500)
		{
			if(nameIndex > 2)
			{
				return;
			}
			GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(cursorID);
			index--;
			if(index < 1)
			{
				index = 62;
			}
			wait = 6;
			break;
		}
		if(GetInput(0, ANALOG_Y) > 500)
		{
			if(nameIndex > 2)
			{
				return;
			}
			GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(cursorID);
			index += 16;
			if(index > 62)
			{
				index -= 63;
				if(index == 0)
				{
					index = 16;
				}
				if(index == 63)
				{
					index = 15;
				}
			}
			wait = 6;
			break;
		}
		if(GetInput(0, ANALOG_Y) < -500)
		{
			if(nameIndex > 2)
			{
				return;
			}
			GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(cursorID);
			index -= 16;
			if(index < 1)
			{
				index += 63;
				if(index == 0)
				{
					index = 48;
				}
				if(index == 63)
				{
					index = 47;
				}
			}
			wait = 6;
			break;
		}
		if(GetInput(0, e_Config.key_ok))
		{
			GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(decideID);
			if(nameIndex > 2)
			{
				phase++;
				return;
			}
			name[nameIndex] = charTable[index];
			nameIndex++;
			wait = 10;
			if(nameIndex > 2)
			{
				e_Ranking.InsertRanking(name, score);
			}
		}
		break;
	default:
		GetMedia()->StopBGM();
		GetMedia()->StopSE();
		MoveScene(new CSceneDemo());
	}
}
