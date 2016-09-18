#include "SystemInput.h"
#include "SafeRelease.h"

//=============================================================
// ���p�\�ȃW���C�X�e�B�b�N��񋓂��ď���������
//=============================================================
BOOL CALLBACK EnumJoysticksCallbackWrapper(const DIDEVICEINSTANCE* pdid, VOID* sys_ref)
{
	CSystemInput* system=(CSystemInput*)sys_ref;
	return system->EnumJoysticksCallback(pdid);
}
BOOL CALLBACK CSystemInput::EnumJoysticksCallback(const DIDEVICEINSTANCE* pdid)
{
	LPDIRECTINPUTDEVICE8 pPadDevice=NULL;
	if (!FAILED(pDinput->CreateDevice(pdid->guidInstance, &pPadDevice, NULL)))
	{
		pPadDevices.push_back(pPadDevice);
	}
	return DIENUM_CONTINUE;
}

//=============================================================
// �R���g���[���[�̃v���p�e�B��񋓂��Đݒ肷��
//=============================================================
BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdid, VOID* device)
{
	LPDIRECTINPUTDEVICE8 pPadDevice = (LPDIRECTINPUTDEVICE8)device;
	if (pdid->dwType & DIDFT_AXIS) {
		DIPROPRANGE dip;
		dip.diph.dwSize = sizeof(DIPROPRANGE);
		dip.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dip.diph.dwHow = DIPH_BYID;
		dip.diph.dwObj = pdid->dwType;
		dip.lMin= -1000;
		dip.lMax= 1000;
		// �p�b�h�̐ݒ�
		pPadDevice->SetProperty(DIPROP_RANGE, &dip.diph);
	}
	return DIENUM_CONTINUE;
}

//=============================================================================================================================

CSystemInput::CSystemInput(CGameHolding *_holding, HWND hWnd)
: CSystemBase(_holding)
{
	pDinput = NULL;
	pPadDevices.clear();
	if(FAILED(InitDinput(hWnd)))
	{
		MessageBox(0, "DirectInput�̏������Ɏ��s", "", MB_OK);
		return;
	}
	// �ő�v���C���[�̓W���C�X�e�B�b�N�f�o�C�X��
	maxPlayer = max(pPadDevices.size(), 1);
	// �R���g���[���[���쐬
	controllers = new CPlayController[maxPlayer];
}

CSystemInput::~CSystemInput()
{
	SAFE_DELETE_ARRAY(controllers);
	SAFE_RELEASE(pKeyDevice);
	for(int i=0, n=pPadDevices.size(); i<n; i++)
	{
		SAFE_RELEASE(pPadDevices[i]);
	}
	pPadDevices.clear();
	SAFE_RELEASE(pDinput);
}

HRESULT CSystemInput::InitDinput(HWND hWnd)
{
	// DirectInput�̍쐬
	if(FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		return E_FAIL;
	}

	// �W���C�X�e�B�b�N�f�o�C�X�̗񋓋y�ю擾
	if(FAILED(pDinput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallbackWrapper, this, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}
	// �e�W���C�X�e�B�b�N�f�o�C�X��ݒ肷��
	for(int i=0, n=pPadDevices.size(); i<n; i++)
	{
		if(FAILED(pPadDevices[i]->SetDataFormat(&c_dfDIJoystick2)))
		{
			return E_FAIL;
		}
		if(FAILED(pPadDevices[i]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		{
			return E_FAIL;
		}
		if(FAILED(pPadDevices[i]->EnumObjects(EnumObjectsCallback, pPadDevices[i], DIDFT_ALL)))
		{
			return E_FAIL;
		}
	}

	// �L�[�{�[�h�f�o�C�X�̎擾�y�ѐݒ�
	if(FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		return E_FAIL;
	}
	if(FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	if(FAILED(pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return E_FAIL;
	}

	// ���t���b�V��
	Reflesh();

	return S_OK;
}

void CSystemInput::Update()
{
	// �L�[�{�[�h�̓��͏��擾
	BYTE diks[256];
	pKeyDevice->GetDeviceState(sizeof(diks), &diks);
	// �W���C�X�e�B�b�N�̓��͏��擾
	DIJOYSTATE2 *js = new DIJOYSTATE2[pPadDevices.size()];
	for(int i=0, n=pPadDevices.size(); i<n; i++)
	{
		pPadDevices[i]->GetDeviceState(sizeof(DIJOYSTATE2), &js[i]);
	}

	// ���͏��Ɋ�Â��ăR���g���[���[�Ƀf�[�^��ݒ�
	if(diks[DIK_LEFT] & 0x80) controllers[0].SetAnalogX(-1000);
	if(diks[DIK_RIGHT] & 0x80) controllers[0].SetAnalogX(1000);
	if(diks[DIK_UP] & 0x80) controllers[0].SetAnalogY(-1000);
	if(diks[DIK_DOWN] & 0x80) controllers[0].SetAnalogY(1000);
	if(diks[DIK_Z] & 0x80) controllers[0].PushKey(0);
	if(diks[DIK_X] & 0x80) controllers[0].PushKey(1);
	if(diks[DIK_C] & 0x80) controllers[0].PushKey(2);
	if(diks[DIK_V] & 0x80) controllers[0].PushKey(3);
	if(diks[DIK_A] & 0x80) controllers[0].PushKey(4);
	if(diks[DIK_S] & 0x80) controllers[0].PushKey(5);
	if(diks[DIK_D] & 0x80) controllers[0].PushKey(6);
	if(diks[DIK_F] & 0x80) controllers[0].PushKey(7);
	if(diks[DIK_Q] & 0x80) controllers[0].PushKey(8);
	if(diks[DIK_W] & 0x80) controllers[0].PushKey(9);
	if(diks[DIK_E] & 0x80) controllers[0].PushKey(10);
	if(diks[DIK_R] & 0x80) controllers[0].PushKey(11);
	if(diks[DIK_RETURN] & 0x80) controllers[0].PushKey(12);
	if(diks[DIK_BACKSPACE] & 0x80) controllers[0].PushKey(13);
	if(diks[DIK_SPACE] & 0x80) controllers[0].PushKey(14);
	if(diks[DIK_LSHIFT] & 0x80) controllers[0].PushKey(15);

	for(int i=0, n=pPadDevices.size(); i<n; i++)
	{
		controllers[i].SetAnalogX(js[i].lX);
		controllers[i].SetAnalogY(js[i].lY);
		for(int j=0; j<KEYNUM; j++)
		{
			if(js[i].rgbButtons[j] & 0x80) controllers[i].PushKey(j);
		}
	}
	SAFE_DELETE_ARRAY(js);

	// �R���g���[���[���̍X�V
	for(int i=0; i<maxPlayer; i++)
	{
		controllers[i].Update();
	}
}

void CSystemInput::Reflesh()
{
	pKeyDevice->Acquire();
	for(int i=0, n=pPadDevices.size(); i<n; i++)
	{
		pPadDevices[i]->Acquire();
	}
}

int CSystemInput::GetInput(int controllerNumber, int keyNumber)
{
	if(controllerNumber > maxPlayer)
	{
		return 0;
	}

	return controllers[controllerNumber].GetKey(keyNumber);
}

void CSystemInput::SetVibration(int controllerNumber, int power, int time)
{
	// ������
}
