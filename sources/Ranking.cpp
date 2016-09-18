#include "Ranking.h"

#include "bgeString.h"

#include <iostream>
#include <fstream>
using namespace std;

CRanking::CRanking()
{
	LoadFile();
}

void CRanking::LoadFile()
{
	ifstream fin("Data/Text/Ranking.txt");
	char s[16];
	for(int i=0; i<5; i++)
	{
		fin >> name[i];
		fin >> s;
		score[i] = GetIntForStr(s);
	}
	fin.close();
}

void CRanking::SaveFile()
{
	ofstream fout("Data/Text/Ranking.txt");
	for(int i=0; i<5; i++)
	{
		fout << name[i] << " " << score[i] << "\n";
	}
	fout.close();
}

void CRanking::ResetRanking()
{
	for(int i=0; i<5; i++)
	{
		strcpy(name[i], "AAA");
		score[i] = 0;
	}
	SaveFile();
}

void CRanking::InsertRanking(char n[], int s)
{
	for(int i=0; i<5; i++)
	{
		if(s > score[i])
		{
			for(int j=4; j>i; j--)
			{
				strcpy(name[j], name[j-1]);
				score[j] = score[j-1];
			}
			strcpy(name[i], n);
			score[i] = s;
			break;
		}
	}
	SaveFile();
}

CRanking e_Ranking;