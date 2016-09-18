#include "Enemy.h"

#include "Dynamics.h"

//=============================================================
// CZako1
//-------------------------------------------------------------
// �O���ɒe�����U�R�G�B
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
