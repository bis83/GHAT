#include "StageScript.h"

#include "bgeString.h"
#include "TaskFactory.h"

#include <iostream>
#include <fstream>

CStageScript::CStageScript()
{
	wait = 0;
	end = true;
	index = 0;
}

CStageScript::~CStageScript()
{
}

void CStageScript::Set(const char *filename)
{
	// ファイルからコマンドリストを作成
	script.clear();
	ifstream fin(filename);
	if(!fin)
	{
		MessageBox(NULL, "StageScriptが存在しません", NULL, MB_OK);
		return;
	}
	char temp[64];
	int i=0;
	SToken t;
	while(!fin.eof())
	{
		fin >> temp;
		if(!strcmp(temp, "WAIT")) {
			t.type = 1;
			fin >> temp;
			t.pattern = GetIntForStr(temp);

			script.push_back(t);
			i++;
		} else if(!strcmp(temp, "ENEMY")) {
			t.type = 2;
			fin >> temp;
			t.id = GetIntForStr(temp);
			fin >> temp;
			t.pattern = GetIntForStr(temp);
			fin >> temp;
			t.vec.x = GetFloatForStr(temp);
			fin >> temp;
			t.vec.y = GetFloatForStr(temp);
			fin >> temp;
			t.vec.z = GetFloatForStr(temp);

			script.push_back(t);
			i++;
		} else if(!strcmp(temp, "BOSS")) {
			t.type = 3;
			fin >> temp;
			t.id = GetIntForStr(temp);

			script.push_back(t);
			i++;
		} else if(!strcmp(temp, "BACK")) {
			t.type = 4;
			fin >> temp;
			t.id = GetIntForStr(temp);

			script.push_back(t);
			i++;
		} else if(!strcmp(temp, "NEXT")) {
			t.type = 5;
			fin >> temp;
			t.id = GetIntForStr(temp);

			script.push_back(t);
			i++;
		} else if(!strcmp(temp, "END")) {
			t.type = 6;

			script.push_back(t);
			i++;
		} else if(!strcmp(temp, "ASTEROID")) {
			t.type = 7;
			fin >> temp;
			t.id = GetIntForStr(temp);
			fin >> temp;
			t.vec.x = GetFloatForStr(temp);
			fin >> temp;
			t.vec.y = GetFloatForStr(temp);
			
			script.push_back(t);
			i++;
		}
	}
	fin.close();
	t.type = 0;
	script.push_back(t);

	wait = 0;
	end = false;
	index = 0;
}

bool CStageScript::Update()
{
	if(wait > 0)
	{
		wait--;
		return true;
	}
	if(end)
	{
		return true;
	}
	// 行を読んで実行する
	while(wait <= 0 && !end)
	{
		switch(script[index].type)
		{
		case 0:		// 終了地点
			end = true;
			break;
		case 1:		// 待機
			wait = script[index].pattern;
			break;
		case 2:		// 敵
			e_taskFactory.CreateEnemy(script[index].id, script[index].pattern, script[index].vec);
			break;
		case 3:		// ボス
			e_taskFactory.CreateBoss(script[index].id);
			break;
		case 4:		// 背景
			e_taskFactory.CreateBack(script[index].id);
			break;
		case 5:		// ステージ
			e_taskMgr.back->ClearTask();
			e_taskMgr.rig->ClearTask();
			switch(script[index].id)
			{
			case 1:
				Set("Data/Text/Stage1.txt");
				return true;
			case 2:
				Set("Data/Text/Stage2.txt");
				return true;
			case 3:
				Set("Data/Text/Stage3.txt");
				return true;
			case 4:
				Set("Data/Text/Stage4.txt");
				return true;
			case 5:
				Set("Data/Text/Stage5.txt");
				return true;
			}
			break;
		case 6:		// エンディング
			return false;
			break;
		case 7:		// アステロイド
			e_taskFactory.CreateRig(1, D3DXVECTOR3(2.5f, script[index].vec.x, 0.0f), D3DXVECTOR3(script[index].vec.y, 0.0f, 0.0f));
			break;
		}
		index++;
	}
	return true;
}

void CStageScript::BossEnd()
{
	wait = 0;
}