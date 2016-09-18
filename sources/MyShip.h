#ifndef MYSHIP_H
#define MYSHIP_H

#include "Thing.h"
#include "Dynamics.h"

//=============================================================
// CMyShip
//-------------------------------------------------------------
// 自機の情報を持つクラス。
// ゲーム中には一体しか存在しないので特別なクラスとして用意する。
//=============================================================
class CMyShip : public CThingMesh
{
public:
	CMyShip();
	// 初期化(メインシーン開始時のセットアップ)
	void Init(CHandleGraphics* hGrap);
	// 更新
	void Update(int a, int b, int anaX, int anaY, CHandleMedia *hMedi);
	// 描画
	void Draw(CHandleGraphics* hGrap);
	// 出現
	bool Revive();
	// 残機の取得
	int GetRest();
	// スコアの取得
	int GetScore();
	// スコアの加算
	void AddScore(int pt);
	// 死亡
	void Dead();
	// ウェポン取得
	void GainWeapon(int wn);

	// 当たり判定
	CBoundingSphere hitRange;
	// アイテムの回収範囲
	CBoundingSphere itemCollectRange;
	bool Blink()
	{
		return blink ? true : false;
	}
	bool Gather()
	{
		return gathering;
	}
	int GetBullet() 
	{
		return restShot;
	}
	bool Equipping()
	{
		return weaponID ? true : false;
	}
	int GetWeaponID()
	{
		return weaponID;
	}
	int GetCharge()
	{
		return min(t_charge * 100 / 30, 100);
	}
private:
	// ショット
	void Shot(int shotNumber);

	// スコア
	int score;
	// 残機
	int restShip;
	// 無敵時間
	int blink;
	// 自機の種類
	int shipType;
	// 現在所持している武器タイプ
	int weaponID;
	// 触手チャージ完了フラグ
	bool tentacle;
	int t_charge;
	// 残弾数
	int restShot;
	// 死亡判定
	bool dead;
	// 回収判定
	bool gathering;
	int g_charge;

	// 最終移動ラジアン角
	float lastMoveRad;

	// 武器グラフィックID
	int weaponGrapID[8];
};

extern CMyShip e_MyShip;

#endif