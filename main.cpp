
#if 0


#include "main.h"
#include "manager.h"
#include <thread>


const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "戦車ゲーム";
POINT lastmousePos;
POINT cursorpos;


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//グローバル変数
HWND g_Window;
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pImmediateContext = nullptr;
POINT g_centerPoint;	//画面の中心座標

bool g_cursorMovedLeft = false;
bool g_cursorMovedRight = false;
int mouseX;
int mouseY;

HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);


		RECT rc = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		g_Window = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);



	}



	Manager::Init();
	ShowCursor(false);
	GetCursorPos(&lastmousePos);
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);




	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;



	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else
		{

			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				GetCursorPos(&cursorpos);
				SetCursorPos(lastmousePos.x, lastmousePos.y);
				Manager::Update();
				Manager::Draw();
			}
		}
	}


	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();

	return (int)msg.wParam;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_MOUSEMOVE:
	{

		//POINT cursorPos;
		//GetCursorPos(&cursorPos);

		////画面内の座標に変換する
		//ScreenToClient(hWnd, &cursorPos);
		//mouseX = cursorPos.x;
		//mouseY = cursorPos.y;
		break;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
float GetMouseCursorPosX() { return cursorpos.x - lastmousePos.x; }
float GetMouseCursorPosY() { return cursorpos.y - lastmousePos.y; }






#else

#include "main.h"
#include "manager.h"
#include <thread>


const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "DX11ゲーム";

#define FRAME_RATE 60
#define TIMER_INTERVAL (1000 / FRAME_RATE) // ゲームのフレームレートに合わせたタイマー設定
UINT_PTR TimerID;	//タイマーのID
POINT lastmousePos;
POINT cursorpos;

bool Pause = false; //ポーズフラグ
bool isGameRunning = true;// ゲーム状態や変数
int Count = 0;		//2回目でフラグを解除するためのカウント
DWORD pauseStartTime = 0; // ポーズ開始時の時間

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//グローバル変数
HWND g_Window;
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pImmediateContext = nullptr;
POINT g_centerPoint;	//画面の中心座標

bool g_cursorMovedLeft = false;
bool g_cursorMovedRight = false;
int mouseX;
int mouseY;

HWND GetWindow()
{
	return g_Window;
}

// タイマーイベントハンドラ
VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	// ゲームのアップデートと描画を行う
	if (!Pause) {

		Manager::Update();
		Manager::Draw();
		
		GetCursorPos(&cursorpos);

		if (Pause == false) {
			SetCursorPos(lastmousePos.x, lastmousePos.y);
			ShowCursor(false);
		}
		else
		{
			ShowCursor(true);
		}
	}
	
	if (!isGameRunning) {
		KillTimer(NULL, 1); // タイマーを停止
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0; 
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);


		RECT rc = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		g_Window = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);	
	}



	Manager::Init();
	// タイマーを設定
	SetTimer(NULL, TimerID, TIMER_INTERVAL, TimerProc);

	ShowCursor(false);
	GetCursorPos(&lastmousePos);
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);




	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;



	MSG msg;
	while(isGameRunning)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				isGameRunning = false;
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

        }
		/*else
		{

			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				GetCursorPos(&cursorpos);
				SetCursorPos(lastmousePos.x,lastmousePos.y);
				Manager::Update();
				Manager::Draw();
			}
		}*/
	}
	// タイマーを削除
	KillTimer(NULL, TimerID);

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();

	return (int)msg.wParam;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
			case 'I':
			{
				if (Pause) {
					// ポーズ解除時に経過時間を考慮してタイマーを再設定
					DWORD elapsedPauseTime = GetTickCount() - pauseStartTime;
					SetTimer(NULL, 1, TIMER_INTERVAL - elapsedPauseTime, TimerProc);
				}
				else {
					// ポーズ開始時に現在のシステム時間を記録
					pauseStartTime = GetTickCount();
					KillTimer(NULL, 1); // タイマーを停止
				}
				Pause = !Pause;
				//DestroyWindow(hWnd);
				break;
			}
		}
		break;
		
	case WM_MOUSEMOVE:
	{
		break;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
float GetMouseCursorPosX() { return cursorpos.x - lastmousePos.x; }
float GetMouseCursorPosY() { return cursorpos.y - lastmousePos.y; }


#endif // 1

