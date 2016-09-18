#ifndef TENTACLE_H
#define TENTACLE_H

#include "Shot.h"
#include "MyShip.h"

//=============================================================
// CTentacle
//-------------------------------------------------------------
// �G��N���X�B���@�ˑ��ŏ�Ɉʒu���C������B
// �A�j���[�V�����ɍ��킹�ē����蔻�肪�ω�����B
// ��莞�Ԃŏ��ł���B�G�ɍU�������Ƃ��A�����ID���擾���āA
// ���@�������������Ȃ��ꍇ�͑�������B
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
	// �G��̐�������
	int timer;
};

#endif