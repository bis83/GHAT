#include "GameHolding.h"
#include "SceneStart.h"

#define STR_GAMENAME "G.H.A.T."

#include <windows.h>

// �E�B���h�E�v���V�[�W��
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
// WINAPI ���C���֐�(�G���g���[�|�C���g)
//=============================================================
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	char clsName [] = "Game by Bis 0001";	// �E�B���h�E�N���X��
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wcex;
	//--------------------------------------------
	// �E�B���h�E�N���X�̓o�^
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
	// �E�B���h�E�N���X�̍쐬
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
	// �E�B���h�E�T�C�Y�̕ύX
	//--------------------------------------------
	SetCenterWindowSize(hWnd, 1280, 720);
	//--------------------------------------------
	// �E�B���h�E�̕\��
	//--------------------------------------------
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	ValidateRect(hWnd, 0);	// �`�惋�[�`�����Ă΂Ȃ��悤�ɂ���

	CGameHolding* game = new CGameHolding(hWnd);
	game->GetScene()->MoveScene(new CSceneStart());
	//--------------------------------------------
	// ���C�����[�v
	//--------------------------------------------
	ZeroMemory(&msg, sizeof(msg));
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			// ���b�Z�[�W�̖|��A���M
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if(msg.message == WM_SETFOCUS)
			{
				game->Reflesh();
			}
		} else {
			// ���C�����[�v
			game->Update();
		}
	}
	// �Q�[���̉��
	delete game;
	// �I��
	return 0;
}

//=============================================================
// �E�B���h�E�v���V�[�W���֐�
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
