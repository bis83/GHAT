#ifndef RANKING_H
#define RANKING_H

//=============================================================
// CRanking
//-------------------------------------------------------------
// ランキング情報の管理を行うクラス。
//=============================================================
class CRanking
{
public:
	CRanking();

	void LoadFile();
	void SaveFile();
	void ResetRanking();
	// ランキングへの追加
	void InsertRanking(char n[], int s);

	// トップ5の名前とスコア
	char name[5][4];
	int score[5];
};

extern CRanking e_Ranking;

#endif