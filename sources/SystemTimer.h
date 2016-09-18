#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H

#include <windows.h>

#include "GameHolding.h"

#pragma comment(lib, "winmm.lib")

//=============================================================
// CSystemTimer
//-------------------------------------------------------------
// FPSを計測するシステムクラス
//=============================================================
class CSystemTimer : public CSystemBase
{
public:
	// コンストラクタ、デストラクタ
	CSystemTimer(CGameHolding* _holding, int new_fps);
	~CSystemTimer();

	// 更新
	void Update();
	// FPSの取得
	int GetFPS();
	// FPSの設定
	void SetFPS(int new_fps);
	// FPS表示の切り替え
	void SetShowFPS(bool flag);
protected:
private:
	// FPS
	int fps;
	// 現在のフレーム、前フレーム
	int frame, prevFrame;
	// 現在時間、前フレームの時間、理想時間、経過時間
	DWORD nowTime, prevTime, idealTime, progress;
	// FPSの表示フラグ
	bool showFPS;
};

#endif
