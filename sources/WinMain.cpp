#include "GameHolding.h"
#include "SceneStart.h"

#define STR_GAMENAME "G.H.A.T."

#include <windows.h>

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void SetCenterWindowSize(HWND hWnd, int width, int height)
{
	RECT rect;
	int cw, ch, ww, wh, sx, sy;
	GetClientRect(hWnd, &rect);
	cw = rect.right - rect.left;
	ch = rect.bottom - rect.top;
	GetWindowRect(hWnd, &rect);
	ww = rect.right - rect.left;
	wh = rect.bottom - rect.top;
	ww = width + ww - cw;
	wh = height + wh - ch;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &rect, NULL);
	sx = rect.right - rect.left;
	sy = rect.bottom - rect.top;
	sx = (sx - ww) / 2;
	sy = (sy - wh) / 2;
	SetWindowPos(hWnd, HWND_TOP, sx, sy, ww, wh, NULL);
}

//=============================================================
// WINAPI メイン関数(エントリーポイント)
//=============================================================
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	char clsName [] = "Game by Bis 0001";	// ウィンドウクラス名
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wcex;
	//--------------------------------------------
	// ウィンドウクラスの登録
	//--------------------------------------------
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = NULL;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = NULL;
	wcex.hIconSm = NULL;
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = (LPCSTR)clsName;
	if (RegisterClassEx(&wcex) == 0) return FALSE;
	//--------------------------------------------
	// ウィンドウクラスの作成
	//--------------------------------------------
	hWnd = CreateWindow((LPCSTR)clsName,
		STR_GAMENAME,
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL);
	//--------------------------------------------
	// ウィンドウサイズの変更
	//--------------------------------------------
	SetCenterWindowSize(hWnd, 1280, 720);
	//--------------------------------------------
	// ウィンドウの表示
	//--------------------------------------------
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	ValidateRect(hWnd, 0);	// 描画ルーチンを呼ばないようにする

	CGameHolding* game = new CGameHolding(hWnd);
	game->GetScene()->MoveScene(new CSceneStart());
	//--------------------------------------------
	// メインループ
	//--------------------------------------------
	ZeroMemory(&msg, sizeof(msg));
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			// メッセージの翻訳、送信
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if(msg.message == WM_SETFOCUS)
			{
				game->Reflesh();
			}
		} else {
			// メインループ
			game->Update();
		}
	}
	// ゲームの解放
	delete game;
	// 終了
	return 0;
}

//=============================================================
// ウィンドウプロシージャ関数
//=============================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_SETFOCUS:
		break;
	case WM_KILLFOCUS:
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
