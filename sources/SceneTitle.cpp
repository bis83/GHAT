#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneDemo.h"

#include "Config.h"
#include "Ranking.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init(CSystemScene *_system)
{
	CSceneBase::Init(_system);
	// 各データのIDを取得
	backID = GetGraphics()->GetDrawObjectID("Data/Mesh/bluePlanet.x");
	titleID = GetGraphics()->GetDrawObjectID("Data/Texture/title.png");
	menuID[0] = GetGraphics()->GetDrawObjectID("Data/Texture/tm_GameStart.png");
	menuID[1] = GetGraphics()->GetDrawObjectID("Data/Texture/tm_Ranking.png");
	menuID[2] = GetGraphics()->GetDrawObjectID("Data/Texture/tm_Config.png");
	menuID[3] = GetGraphics()->GetDrawObjectID("Data/Texture/tm_Exit.png");
	fontID = GetGraphics()->GetDrawObjectID("Data/Texture/font.png");
	particleID = GetGraphics()->GetDrawObjectID("Data/Texture/particle.png");

	decideID = GetMedia()->GetMediaObjectID("Data/Media/decide.wav");
	cancelID = GetMedia()->GetMediaObjectID("Data/Media/cancel.wav");
	cursorID = GetMedia()->GetMediaObjectID("Data/Media/cursor.wav");
	bgmID = GetMedia()->GetMediaObjectID("Data/Media/loop.wav");
	// 各変数の初期化
	phase = 0;
	step = 0;
	index = 0;
	wait = 30;
	time = 0;
	demo_time = 0;
	srand(timeGetTime());
	for(int i=0; i<32; i++)
	{
		vecParticlePos[i].x = rand() % 1380;
		vecParticlePos[i].y = rand() % 680;
		particleScaling[i] = (rand() % 4 + 1) * 0.10f + 0.8f;
	}
	// 音楽の再生
	GetMedia()->SetPlayStatus(bgmID, MOS_VOLUME, &e_Config.bgm_volume);
	GetMedia()->PlayBGM(bgmID, 0);
}

void CSceneTitle::UnInit()
{
}

void CSceneTitle::Update()
{
	// 背景パーティクルの移動
	for(int i=0; i<32; i++)
	{
		vecParticlePos[i].x += 1 * particleScaling[i];
		if(vecParticlePos[i].x > 1280+128)
		{
			vecParticlePos[i].x -= 1600;
		}
	}
	// タイマーの更新
	time++;
	// 待機命令がある場合は待機する
	if(wait > 0)
	{
		wait--;
		return;
	}
	// フェーズによって分岐
	switch(phase)
	{
	case 0:		// メイン
		demo_time++;
		// 選択肢の移動
		if(GetInput(0, ANALOG_Y)>500)
		{
			index++;
			if(index > 3) index = 0;
			wait = 10;
			GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(cursorID);
			demo_time = 0;
			return;
		} else if(GetInput(0, ANALOG_Y)<-500)
		{
			index--;
			if(index < 0) index = 3;
			wait = 10;
			GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(cursorID);
			demo_time = 0;
			return;
		}
		// 選択肢
		if(GetInput(0, e_Config.key_ok) == 1)
		{
			switch(index)
			{
			case 0:		// GameStart
				// シーンの移行
				MoveScene(new CSceneMain());
				GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(decideID);
				GetMedia()->StopBGM();
				demo_time = 0;
				break;
			case 1:		// Ranking
				phase = 1;
				wait = 10;
				GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(decideID);
				demo_time = 0;
				break;
			case 2:		// Config
				index = 0;
				phase = 2;
				wait = 10;
				GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(decideID);
				demo_time = 0;
				break;
			case 3:		// exit
				GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(decideID);
				demo_time = 0;
				GameEnd();
				break;
			}
			return;
		}
		// デモへの移行
		if(demo_time > 720)
		{
			GetMedia()->StopBGM();
			MoveScene(new CSceneDemo());
		}
		break;
	case 1:		// ランキング
		if(GetInput(0, e_Config.key_cancel) == 1)
		{
			phase = 0;
			wait = 10;
			GetMedia()->SetPlayStatus(cancelID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(cancelID);
			break;
		}
		break;
	case 2:		// コンフィグ
		// 選択肢の移動
		if(GetInput(0, ANALOG_Y)>500)
		{
			index++;
			if(index > 11) index = 0;
			wait = 10;
			break;
		} else if(GetInput(0, ANALOG_Y)<-500)
		{
			index--;
			if(index < 0) index = 11;
			wait = 10;
			break;
		}
		// 左右はボリュームの調節および残機と難易度の調節用
		if(GetInput(0, ANALOG_X)>500)
		{
			switch(index)
			{
			case 5:
				e_Config.bgm_volume += 10;
				if(e_Config.bgm_volume > 100)
					e_Config.bgm_volume = 100;
				wait = 5;
				GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(cursorID);
				GetMedia()->SetPlayStatus(bgmID, MOS_VOLUME, &e_Config.bgm_volume);
				break;
			case 6:
				e_Config.se_volume += 10;
				if(e_Config.se_volume > 100)
					e_Config.se_volume = 100;
				wait = 5;
				GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(cursorID);
				break;
			case 7:
				e_Config.rest++;
				if(e_Config.rest > 9)
					e_Config.rest = 1;
				wait = 10;
				GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(cursorID);
				break;
			case 8:
				e_Config.difficult++;
				if(e_Config.difficult > 5)
					e_Config.difficult = 1;
				wait = 10;
				GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(cursorID);
				break;
			}
			break;;
		} else if(GetInput(0, ANALOG_X)<-500)
		{
			switch(index)
			{
			case 5:
				e_Config.bgm_volume -= 10;
				if(e_Config.bgm_volume < 0)
					e_Config.bgm_volume = 0;
				wait = 5;
				GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(cursorID);
				GetMedia()->SetPlayStatus(bgmID, MOS_VOLUME, &e_Config.bgm_volume);
				break;
			case 6:
				e_Config.se_volume -= 10;
				if(e_Config.se_volume < 0)
					e_Config.se_volume = 0;
				wait = 5;
				GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(cursorID);
				break;
			case 7:
				e_Config.rest--;
				if(e_Config.rest < 1)
					e_Config.rest = 9;
				wait = 10;
				GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(cursorID);
				break;
			case 8:
				e_Config.difficult--;
				if(e_Config.difficult < 1)
					e_Config.difficult = 5;
				wait = 10;
				GetMedia()->SetPlayStatus(cursorID, MOS_VOLUME, &e_Config.se_volume);
				GetMedia()->PlaySE(cursorID);
				break;
			}
			break;
		}

		// ランキングのリセット
		if(GetInput(0, e_Config.key_ok) == 1 && index == 9)
		{
			GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(decideID);
			e_Ranking.ResetRanking();
			wait = 10;
			break;
		}
		// コンフィグデータのセーブ
		if(GetInput(0, e_Config.key_ok) == 1 && index == 10)
		{
			GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(decideID);
			e_Config.SaveFile();
			wait = 10;
			break;
		}
		// 戻る
		if(GetInput(0, e_Config.key_ok) == 1 && index == 11)
		{
			index = 2;
			phase = 0;
			wait = 10;
			GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
			GetMedia()->PlaySE(decideID);
			break;
		}
		// キーコンフィグ
		// 押した瞬間のボタンを計測する
		for(int i=0; i<KEYNUM; i++)
		{
			if(GetInput(0, i) == 1)
			{
				switch(index)
				{
				case 0:
					e_Config.key_ok = i;
					wait = 10;
					GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
					GetMedia()->PlaySE(decideID);
					break;
				case 1:
					e_Config.key_cancel = i;
					wait = 10;
					GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
					GetMedia()->PlaySE(decideID);
					break;
				case 2:
					e_Config.key_shot = i;
					wait = 10;
					GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
					GetMedia()->PlaySE(decideID);
					break;
				case 3:
					e_Config.key_bomb = i;
					wait = 10;
					GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
					GetMedia()->PlaySE(decideID);
					break;
				case 4:
					e_Config.key_pause = i;
					wait = 10;
					GetMedia()->SetPlayStatus(decideID, MOS_VOLUME, &e_Config.se_volume);
					GetMedia()->PlaySE(decideID);
					break;
				}
				break;
			}
		}
		break;
	}
}

void CSceneTitle::Draw()
{
	for(int i=0; i<32; i++)
	{
		D3DXMatrixScaling(&mat2, particleScaling[i], particleScaling[i], 0);
		D3DXMatrixTranslation(&mat, vecParticlePos[i].x, vecParticlePos[i].y, 1);
		D3DXMatrixMultiply(&mat, &mat2, &mat);
		blend = D3DBLEND_ONE;
		GetGraphics()->SetDrawObjectStatus(particleID, DOS_SRCBLEND, &blend);
		GetGraphics()->SetDrawObjectStatus(particleID, DOS_DESTBLEND, &blend);
		GetGraphics()->SetDrawObjectStatus(particleID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(particleID);
	}
	// 背景の描画
	D3DXMatrixRotationY(&mat, time*D3DX_PI/720);
	GetGraphics()->SetDrawObjectStatus(backID, DOS_MATRIX, &mat);
	GetGraphics()->DrawObject(backID);

	// フェーズによって表示を分岐
	switch(phase)
	{
	case 0:		// タイトル
		// タイトルの描画
		D3DXMatrixTranslation(&mat, 640, 240, 0);
		GetGraphics()->SetDrawObjectStatus(titleID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(titleID);

		// タイトルメニューの描画
		for(int i=0; i<4; i++)
		{
			D3DXMatrixTranslation(&mat, 640, 420+i*60, 0);
			GetGraphics()->SetDrawObjectStatus(menuID[i], DOS_MATRIX, &mat);
			if(i != index)
			{
				color= D3DCOLOR_ARGB(128, 255, 255, 255);
				GetGraphics()->SetDrawObjectStatus(menuID[i], DOS_COLOR, &color);
			}
			GetGraphics()->DrawObject(menuID[i]);
		}
		break;
	case 1:		// ランキング
		D3DXMatrixTranslation(&mat, 400, 48*4, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		sprintf(string, "Ranking");
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);
		for(int i=0; i<5; i++)
		{
			D3DXMatrixTranslation(&mat, 400, 48*5+i*48, 0);
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
			sprintf(string, "%1d_%s__%8d", i+1, e_Ranking.name[i], e_Ranking.score[i]);
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
			GetGraphics()->DrawObject(fontID);
		}
		break;
	case 2:		// コンフィグ
		color = D3DCOLOR_ARGB(128, 255, 255, 255);
		// 各コンフィグデータの表示
		D3DXMatrixTranslation(&mat, 400, 72, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		sprintf(string, "Config");
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);
		// KEY_CONFIG
		// OK
		D3DXMatrixTranslation(&mat, 400, 72+48*1, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 0)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "OK      %2d", e_Config.key_ok);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);
		// CANCEL
		D3DXMatrixTranslation(&mat, 400, 72+48*2, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 1)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "Cancel  %2d", e_Config.key_cancel);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);
		// SHOT
		D3DXMatrixTranslation(&mat, 400, 72+48*3, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 2)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "Shot    %2d", e_Config.key_shot);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);
		// BOMB
		D3DXMatrixTranslation(&mat, 400, 72+48*4, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 3)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "Bomb    %2d", e_Config.key_bomb);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);
		// PAUSE
		D3DXMatrixTranslation(&mat, 400, 72+48*5, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 4)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "Pause   %2d", e_Config.key_pause);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);

		// MEDIA_CONFIG
		// BGM_VOLUME
		D3DXMatrixTranslation(&mat, 400, 72+48*6, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 5)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "BGM Volume  %3d", e_Config.bgm_volume);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);
		// SE_VOLUME
		D3DXMatrixTranslation(&mat, 400, 72+48*7, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 6)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "SE Volume   %3d", e_Config.se_volume);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);

		// GAME_CONFIG
		// REST
		D3DXMatrixTranslation(&mat, 400, 72+48*8, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 7)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "Rest       %1d", e_Config.rest);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);
		// DIFFICULT
		D3DXMatrixTranslation(&mat, 400, 72+48*9, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 8)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "Difficult  %1d", e_Config.difficult);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);

		// RESET_RANKING
		D3DXMatrixTranslation(&mat, 400, 72+48*10, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 9)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "ResetRanking");
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);

		// SAVE_CONFIG_DATA
		D3DXMatrixTranslation(&mat, 400, 72+48*11, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 10)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "Save ConfigData");
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);

		// BACK
		D3DXMatrixTranslation(&mat, 400, 72+48*12, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		if(index != 11)
			GetGraphics()->SetDrawObjectStatus(fontID, DOS_COLOR, &color);
		sprintf(string, "Back");
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		GetGraphics()->DrawObject(fontID);
		break;
	}

	// FPSの描画
	sprintf(string, "FPS_%2d", GetFPS());
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);
}
