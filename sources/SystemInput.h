#ifndef SYSTEMINPUT_H
#define SYSTEMINPUT_H

#include <windows.h>
#include <dinput.h>

#include "GameHolding.h"
#include "PlayController.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#include <vector>
using namespace std;

//=============================================================
// CSystemInput
//-------------------------------------------------------------
// ���͏���ێ�����N���X�B
// ���������ɃQ�[���p�b�h�����擾���āA�v���C���[��������U��B
//=============================================================
class CSystemInput : public CSystemBase
{
public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CSystemInput(CGameHolding* _holding, HWND hWnd);
	~CSystemInput();
	// �X�V
	void Update();
	// ���t���b�V��
	void Reflesh();
	// ���͂̎擾
	int GetInput(int controllerNumber, int keyNumber);
	// �U����^����
	void SetVibration(int controllerNumber, int power, int time);

	// �W���C�X�e�B�b�N�񋓗p�R�[���o�b�N�֐�
	BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdid);
protected:
private:
	// DirectInput�̏�����
	HRESULT InitDinput(HWND hWnd);

	// DirectInput8
	LPDIRECTINPUT8 pDinput;

	// �f�o�C�X
	LPDIRECTINPUTDEVICE8 pKeyDevice;
	vector<LPDIRECTINPUTDEVICE8> pPadDevices;

	// �v���C���[����
	int maxPlayer;
	// �R���g���[���[
	CPlayController* controllers;
};

#endif
