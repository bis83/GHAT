#include "Config.h"

#include "bgeString.h"

#include <iostream>
#include <fstream>
using namespace std;

CConfig::CConfig()
{
	LoadFile();
}

void CConfig::LoadFile()
{
	ifstream fin("Data/Text/Config.txt");
	char str[32];
	while(!fin.eof())
	{
		fin >> str;
		if(!strcmp(str, "OK"))
		{
			fin >> str;
			key_ok = GetIntForStr(str);
			continue;
		}
		if(!strcmp(str, "CANCEL"))
		{
			fin >> str;
			key_cancel = GetIntForStr(str);
			continue;
		}
		if(!strcmp(str, "SHOT"))
		{
			fin >> str;
			key_shot = GetIntForStr(str);
			continue;
		}
		if(!strcmp(str, "BOMB"))
		{
			fin >> str;
			key_bomb = GetIntForStr(str);
			continue;
		}
		if(!strcmp(str, "PAUSE"))
		{
			fin >> str;
			key_pause = GetIntForStr(str);
			continue;
		}
		if(!strcmp(str, "BGM_VOLUME"))
		{
			fin >> str;
			bgm_volume = GetIntForStr(str);
			continue;
		}
		if(!strcmp(str, "SE_VOLUME"))
		{
			fin >> str;
			se_volume = GetIntForStr(str);
			continue;
		}
		if(!strcmp(str, "REST"))
		{
			fin >> str;
			rest = GetIntForStr(str);
			continue;
		}
		if(!strcmp(str, "DIFFICULT"))
		{
			fin >> str;
			difficult = GetIntForStr(str);
			continue;
		}
	}
	fin.close();
}

void CConfig::SaveFile()
{
	ofstream fout("Data/Text/Config.txt");
	fout << "KEY_CONFIG" << "\n";
	fout << "OK" << " " << key_ok << "\n";
	fout << "CANCEL" << " " << key_cancel << "\n";
	fout << "SHOT" << " " << key_shot << "\n";
	fout << "BOMB" << " " << key_bomb << "\n";
	fout << "PAUSE" << " " << key_pause << "\n";
	fout << "\n" << "MEDIA_CONFIG" << "\n";
	fout << "BGM_VOLUME" << " " << bgm_volume << "\n";
	fout << "SE_VOLUME" << " " << se_volume << "\n";
	fout << "\n" << "GAME_CONFIG" << "\n";
	fout << "REST" << " " << rest << "\n";
	fout << "DIFFICULT" << " " << difficult << "\n";
	fout.close();
}

CConfig e_Config;
