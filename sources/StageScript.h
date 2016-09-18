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
// ステージ用スクリプト解析機
//-------------------------------------------------------------
// WAIT(1) timer					timeFだけ処理を停止
// ENEMY(2) id pattern x y z		(x,y,z)からidの敵をpatternで実行
// BOSS(3) id						ステージのボス開始地点。ボスを倒すとステージクリア
// BACK(4) id							idの背景を作成
// NEXT(5)	no							noのステージに移動
// END(6)								エンディングに移動する
// ASTEROID(7) id y vx					隕石(idサイズ)を作成する
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