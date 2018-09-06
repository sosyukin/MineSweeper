// MineSweeper.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "MineSweeper.h"

#include <stack>
#include <time.h>
#define MAX_LOADSTRING 100
// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

GameManager gm;
// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


VOID CALLBACK TimerProc(HWND hWnd, UINT, UINT_PTR, DWORD)
{
	
	//处理WM_TIMER讯息 
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	
 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MINESWEEPER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINESWEEPER));

	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINESWEEPER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MINESWEEPER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU,
	   CW_USEDEFAULT, 0, gm.cxClientSize + 16,gm.cyClientSize + 59, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static int cxPos, cyPos;
	static int cxPrePos, cyPrePos;
	switch (message)
	{
	case WM_LBUTTONDOWN:
		gm.bStateLButtonDown = true;
		cxPos = LOWORD(lParam);
		cyPos = HIWORD(lParam);
		if (gm.ResetButton.isIn(cxPos, cyPos))
		{
			hdc = GetDC(hWnd);
			gm.ResetButton.OnLButtonDown(hdc);
			gm.ResetButton.flagstate = true;
			ReleaseDC(hWnd, hdc);
		}
		if (gm.MineField.isIn(cxPos,cyPos))
		{
			for (int i = 0; i < gm.cxBlockNumber; i++)
			{
				for (int j = 0; j < gm.cyBlockNumber; j++)
				{
					if (gm.MineBlock[i][j].isIn(cxPos, cyPos))
					{
						hdc = GetDC(hWnd);
						if ((wParam & MK_LBUTTON) && (wParam & MK_RBUTTON))
						{
							gm.DoubleButtonDown(hdc, i, j);
						}
						else
						{
							gm.LButtonDown(hdc, i, j);
						}
						ReleaseDC(hWnd, hdc);
						cxPrePos = i;
						cyPrePos = j;
					}
				}
			}
		}
		break;
	case WM_RBUTTONDOWN:
		gm.bStateRButtonDown = true;
		cxPos = LOWORD(lParam);
		cyPos = HIWORD(lParam);
		if (gm.MineField.isIn(cxPos, cyPos))
		{
			for (int i = 0; i < gm.cxBlockNumber; i++)
			{
				for (int j = 0; j < gm.cyBlockNumber; j++)
				{
					if (gm.MineBlock[i][j].isIn(cxPos, cyPos))
					{
						
						if ((wParam & MK_LBUTTON) && (wParam & MK_RBUTTON))
						{
							hdc = GetDC(hWnd);
							gm.DoubleButtonDown(hdc, i, j);
							ReleaseDC(hWnd, hdc);
							cxPrePos = i;
							cyPrePos = j;
						}
						
						
					}
				}
			}
		}
		break;
	
	case WM_MOUSEMOVE:
		if (gm.bStateLButtonDown)
		{
			
			cxPos = LOWORD(lParam);
			cyPos = HIWORD(lParam);
			if (gm.ResetButton.isIn(cxPos, cyPos))
			{
				hdc = GetDC(hWnd);
				gm.ResetButton.OnLButtonDown(hdc);
				gm.ResetButton.flagstate = true;
				ReleaseDC(hWnd, hdc);
			}
			else if (gm.ResetButton.flagstate)
			{
				hdc = GetDC(hWnd);
				gm.ResetButton.Paint(hdc);
				gm.ResetButton.flagstate = false;
				ReleaseDC(hWnd, hdc);
			}
			if (gm.MineField.isIn(cxPos,cyPos))
			{
				for (int i = 0; i < gm.cxBlockNumber; i++)
				{
					for (int j = 0; j < gm.cyBlockNumber; j++)
					{
						if (gm.MineBlock[i][j].isIn(cxPos, cyPos) && (i != cxPrePos || j != cyPrePos))
						{
							hdc = GetDC(hWnd);
							if ((wParam & MK_LBUTTON) && (wParam & MK_RBUTTON))
							{
								gm.DoubleButtonRecover(hdc, cxPrePos, cyPrePos);
								gm.DoubleButtonDown(hdc, i, j);
							}
							else
							{
								gm.PaintBlock(hdc, cxPrePos, cyPrePos);
								gm.LButtonDown(hdc, i, j);
							}
							ReleaseDC(hWnd, hdc);
							cxPrePos = i;
							cyPrePos = j;
						}
					}
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		if (gm.bStateLButtonDown)
		{
			gm.bStateLButtonDown = false;
			cxPos = LOWORD(lParam);
			cyPos = HIWORD(lParam);
			if (gm.ResetButton.isIn(cxPos, cyPos))
			{
				RECT rect;
				GetClientRect(hWnd, &rect);
				gm.Reset(hWnd, &rect);
			}
			if (gm.MineField.isIn(cxPos, cyPos))
			{
				for (int i = 0; i < gm.cxBlockNumber; i++)
				{
					for (int j = 0; j < gm.cyBlockNumber; j++)
					{
						if (gm.MineBlock[i][j].isIn(cxPos, cyPos))
						{
							if (gm.bStateFirstClick)
							{
								gm.bStateFirstClick = false;
								gm.SetMine(i, j);
								gm.TimeCounter.Start(hWnd);
							}
							hdc = GetDC(hWnd);
							if ((wParam & MK_RBUTTON))
							{
								gm.DoubleButtonUp(hdc, i, j);
								gm.bStateRButtonDown = false;
							}
							else
							{
								gm.LButtonUp(hdc, i, j);
								
							}
							if (gm.Judgment())
							{
								gm.GameOver(hWnd, hdc);
								
							}
							//胜负判断与显示扩张
							ReleaseDC(hWnd, hdc);
						}
					}
				}
			}
		}

		break;
	case WM_RBUTTONUP:
		if (gm.bStateRButtonDown)
		{
			gm.bStateRButtonDown = false;
			cxPos = LOWORD(lParam);
			cyPos = HIWORD(lParam);
			if (gm.MineField.isIn(cxPos, cyPos))
			{
				for (int i = 0; i < gm.cxBlockNumber; i++)
				{
					for (int j = 0; j < gm.cyBlockNumber; j++)
					{
						if (gm.MineBlock[i][j].isIn(cxPos, cyPos))
						{
							if (gm.bStateFirstClick)
							{
								gm.bStateFirstClick = false;
								gm.SetMine(i, j);
								gm.TimeCounter.Start(hWnd);
							}
							hdc = GetDC(hWnd);
							if ((wParam & MK_LBUTTON))
							{
								gm.bStateLButtonDown = false;
								gm.DoubleButtonUp(hdc, i, j);
							}
							else
							{
								gm.RButtonUp(hdc, i, j);
							}
							ReleaseDC(hWnd, hdc);
						}
					}
				}
			}
		}

		break;
	case WM_CREATE:
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_TIMER:
		hdc = GetDC(hWnd);
		gm.TimeCounter.Refresh(hdc);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		gm.GlobalBackground.Paint(hdc);
		gm.ControlBar.Paint(hdc);
		gm.FlagCounter.Paint(hdc);
		gm.TimeCounter.Paint(hdc);
		gm.ResetButton.Paint(hdc);
		gm.MineField.Paint(hdc);
		for (int i = 0; i < gm.cxBlockNumber; i++)
		{
			for (int j = 0; j < gm.cyBlockNumber; j++)
			{
				gm.MineBlock[i][j].Paint(hdc);
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}