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
// 入力情報を保持するクラス。
// 初期化時にゲームパッド数を取得して、プレイヤー数を割り振る。
//=============================================================
class CSystemInput : public CSystemBase
{
public:
	// コンストラクタ、デストラクタ
	CSystemInput(CGameHolding* _holding, HWND hWnd);
	~CSystemInput();
	// 更新
	void Update();
	// リフレッシュ
	void Reflesh();
	// 入力の取得
	int GetInput(int controllerNumber, int keyNumber);
	// 振動を与える
	void SetVibration(int controllerNumber, int power, int time);

	// ジョイスティック列挙用コールバック関数
	BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdid);
protected:
private:
	// DirectInputの初期化
	HRESULT InitDinput(HWND hWnd);

	// DirectInput8
	LPDIRECTINPUT8 pDinput;

	// デバイス
	LPDIRECTINPUTDEVICE8 pKeyDevice;
	vector<LPDIRECTINPUTDEVICE8> pPadDevices;

	// プレイヤー総数
	int maxPlayer;
	// コントローラー
	CPlayController* controllers;
};

#endif
