#ifndef BOSS_H
#define BOSS_H

#include "Thing.h"
#include "Dynamics.h"

//=============================================================
// CBoss
//-------------------------------------------------------------
// ボス基底クラス。
//=============================================================
class CBoss : public CThingMesh
{
public:
	CBoss() {}
	virtual ~CBoss() {};
	
	virtual bool Update(CHandleMedia *hMedi) = 0;
	virtual bool Hit(CDynamics *target) = 0;
	virtual void Draw(CHandleGraphics *hGrap) = 0;
	void Damage(int d) {
		life -= d;
	}
protected:
	int life;
	int pattern;
	int act;
	int timer;
};

//=============================================================
// CBoss1
//-------------------------------------------------------------
// ステージ1,3ボス。
//-------------------------------------------------------------
// pattern1 : 3wayバルカン
// pattern2 : ミサイル
// pattern3 : zako2射出
// pattern4 : 自機狙いバルカン+ミサイル
// pattern5 : zako6出現
// pattern6 : 高速ワインダー
// 1~6を繰り返す(3週で自爆)
//=============================================================
class CBoss1 : public CBoss
{
public:
	CBoss1(CHandleGraphics *hGrap, CHandleMedia *hMedi);
	~CBoss1();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
private:
	CBoundingSphere hit[3];
	int loop;
	int shotSoundID[3];
};

//=============================================================
// CBoss2
//-------------------------------------------------------------
// ステージ2,4ボス。
// ステージ2では隕石が障害物として登場する。
//-------------------------------------------------------------
// pattern1 : 移動なし+全方位10way弾
// pattern2 : 時機依存縦移動+自機狙い7way
// pattern3 : 移動なし+zako1出現
// pattern4 : 時機依存縦移動+4wayバルカン+ミサイル
// pattern5 : 移動なし+zako5出現
// pattern6 : 時機依存縦移動+高速自機狙い弾+全方位10way
// pattern7 : 移動なし+zako2射出
// pattern8 : 時機依存縦移動+自機狙い高速27way弾
// 1~8を繰り返す(2週で自爆)
//=============================================================
class CBoss2 : public CBoss
{
public:
	CBoss2(CHandleGraphics *hGrap, CHandleMedia *hMedi);
	~CBoss2();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
private:
	CBoundingSphere hit[3];
	int loop;
	// 乱数テーブル
	char s_table[19];
	int s_index;
	int shotSoundID[3];
};

//=============================================================
// CBoss3
//-------------------------------------------------------------
// ステージ5ボス。
//-------------------------------------------------------------
// pattern1 : 自機狙い3way弾		自機依存上下移動
// pattern2 : zako1出現				移動なし
// pattern3 : 大量ミサイル			自機方向に移動
// pattern4 : zako2出現				元のx軸ラインに平行移動
// pattern5 : ランダムバルカン		自機依存上下移動
// pattern6 : 全方位10way+渦巻き弾	移動なし
// pattern7 : zako6出現				移動なし
// pattern8 : 自機狙い高速9way		自機依存上下移動
// pattern9 : 発狂攻撃+zako1出現	画面中央に移動
// 1~8を繰り返す、体力1/8以下でpattern9に移行
//=============================================================
class CBoss3 : public CBoss
{
public:
	CBoss3(CHandleGraphics *hGrap, CHandleMedia *hMedi);
	~CBoss3();

	bool Update(CHandleMedia *hMedi);
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
private:
	CBoundingSphere hit[3];
	int loop;
	int shotSoundID[3];
};

#endif