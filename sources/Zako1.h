#include "Enemy.h"

#include "Dynamics.h"

//=============================================================
// CZako1
//-------------------------------------------------------------
// 前方に弾を撃つザコ敵。
//=============================================================
// 
class CZako1 : public CEnemy
{
public:
	CZako1(CTaskList *taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, int action);
	~CZako1();

	bool Update();
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
	CDynamics* GetDynamics()
	{
		return &hit;
	}
private:
	int timer;
	CBoundingSphere hit;
};
