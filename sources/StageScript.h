#ifndef STAGESCRIPT_H
#define STAGESCRIPT_H

#include <d3dx9.h>
#include <vector>

using namespace std;

typedef struct _SToken {
	int type;
	int id;
	int pattern;
	D3DXVECTOR3 vec;
} SToken;

//=============================================================
// CStageScript
//-------------------------------------------------------------
// �X�e�[�W�p�X�N���v�g��͋@
//-------------------------------------------------------------
// WAIT(1) timer					timeF�����������~
// ENEMY(2) id pattern x y z		(x,y,z)����id�̓G��pattern�Ŏ��s
// BOSS(3) id						�X�e�[�W�̃{�X�J�n�n�_�B�{�X��|���ƃX�e�[�W�N���A
// BACK(4) id							id�̔w�i���쐬
// NEXT(5)	no							no�̃X�e�[�W�Ɉړ�
// END(6)								�G���f�B���O�Ɉړ�����
// ASTEROID(7) id y vx					覐�(id�T�C�Y)���쐬����
//=============================================================
class CStageScript
{
public:
	CStageScript();
	~CStageScript();

	bool Update();
	void Set(const char *filename);
	void BossEnd();
private:
	int index;
	int wait;
	bool end;

	vector<SToken> script;
};

#endif