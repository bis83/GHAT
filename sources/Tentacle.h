#ifndef TENTACLE_H
#define TENTACLE_H

#include "Shot.h"
#include "MyShip.h"

//=============================================================
// CTentacle
//-------------------------------------------------------------
// 触手クラス。自機依存で常に位置を修正する。
// アニメーションに合わせて当たり判定が変化する。
// 一定時間で消滅する。敵に攻撃したとき、相手のIDを取得して、
// 自機が装備を持たない場合は装備する。
//=============================================================
class CTentacle : public CShot
{
public:
	CTentacle(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos);
	~CTentacle();

	bool Update();
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
	CDynamics *GetDynamics()
	{
		return &hit;
	}
private:
	CBoundingSphere hit;
	// 触手の生存時間
	int timer;
};

#endif