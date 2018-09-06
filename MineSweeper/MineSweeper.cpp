// MineSweeper.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MineSweeper.h"

#include <stack>
#include <time.h>
#define MAX_LOADSTRING 100
// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

GameManager gm;
// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


VOID CALLBACK TimerProc(HWND hWnd, UINT, UINT_PTR, DWORD)
{
	
	//����WM_TIMERѶϢ 
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	
 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MINESWEEPER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINESWEEPER));

	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
							//ʤ���ж�����ʾ����
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
		// �����˵�ѡ��: 
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

// �����ڡ������Ϣ�������
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