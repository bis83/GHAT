#ifndef DRAWEVENT_H
#define DRAWEVENT_H

#include <d3dx9.h>

// �e�G�t�F�N�g�r�b�g(|�ŕ���, &�Ŏ���)
#define DEE_BILLBOARD	0x00000001
#define DEE_SKYBOX		0x00000002
#define DEE_SEASERFACE	0x00000004
#define DEE_4			0x00000008
#define DEE_5			0x00000010

// �A���t�@�l(��1�o�C�g��0~255�̃A���t�@�l)
#define DEA_NORMAL		0x00000000
#define DEA_ADDITION	0x00001000
#define DEA_REDUCE		0x00002000

//=============================================================
// SDrawEvent
//-------------------------------------------------------------
// �`��I�u�W�F�N�g��`�悷��C�x���g�B
// �`��C�x���g�L���[�ɕۑ�����Ė��t���[�����Ƃɉ�������B
// 3D�I�u�W�F�N�g�A�X�v���C�g�A�e�L�X�g
//=============================================================
typedef struct _SDrawEvent
{
	// �`��I�u�W�F�N�gID
	int objectID;
	// ���[���h�s��
	D3DXMATRIXA16 matWorld;
	// �A���t�@�l
	int alpha;
	// �G�t�F�N�g
	int effect;
	// ���̃C�x���g
	struct _SDrawEvent* next;
} SDrawEvent;

//=============================================================
// CDrawEventStack
//-------------------------------------------------------------
// �`��C�x���g��ێ�����L���[�N���X
//=============================================================
class CDrawEventStack
{
public:
	// �����ɃC�x���g�̒ǉ�
	void Push(SDrawEvent &ev);
	// �擪�̃C�x���g�̍폜
	void Pop();
	// �擪�̃C�x���g�̎擾
	SDrawEvent* GetFront();

	// �L���[�̍쐬(�ő�C�x���g��)
	void Create(int max_num_event);
	// �C�x���g�̃N�C�b�N�\�[�g
	void Sort();
	// �L���[�̃N���A
	void Clear();
	// ��
	bool Empty();
private:
	SDrawEvent* queue;
	SDrawEvent* active;
	SDrawEvent* free;
};

#endif
