#ifndef RANKING_H
#define RANKING_H

//=============================================================
// CRanking
//-------------------------------------------------------------
// �����L���O���̊Ǘ����s���N���X�B
//=============================================================
class CRanking
{
public:
	CRanking();

	void LoadFile();
	void SaveFile();
	void ResetRanking();
	// �����L���O�ւ̒ǉ�
	void InsertRanking(char n[], int s);

	// �g�b�v5�̖��O�ƃX�R�A
	char name[5][4];
	int score[5];
};

extern CRanking e_Ranking;

#endif