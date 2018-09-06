#include "stdafx.h"
#include "GameManager.h"

#include <time.h>

GameManager::GameManager()
{
	cxBlockNumber = 30;
	cyBlockNumber = 16;
	iMineNumber = 99;
	int x11 = 0, y11 = 0;
	int x21 = x11 + iBorder1;
	int y21 = y11 + iBorder1;
	int x31 = x21 + iBorderSL + iBorder2;
	int y31 = y21 + iBorderSL + iBorder2;
	int x32 = x31 + cxCounter;
	int y32 = y31 + cyCounter;
	int y22 = 2 * (iBorderSL + iBorder2) + cyCounter + iBorder1;
	int x61 = x21;
	int y61 = y22 + iBorder1;
	int x71[30][16], y71[30][16];
	int x72[30][16], y72[30][16];
	for (int i = 0; i < cxBlockNumber; i++)
	{
		for (int j = 0; j < cyBlockNumber; j++)
		{
			x71[i][j] = x61 + iBorderSL + i * cxBlockSize;
			y71[i][j] = y61 + iBorderSL + j*cyBlockSize;
			x72[i][j] = x71[i][j] + cxBlockSize;
			y72[i][j] = y71[i][j] + cyBlockSize;
			RECT rectMineBlock{ x71[i][j], y71[i][j], x72[i][j], y72[i][j] };
			MineBlock[i][j].Reset(rectMineBlock, iBorderSL);
			
		}
	}
	int x62 = x61 + cxBlockSize * cxBlockNumber + 2 * iBorderSL;
	int y62 = y61 + cyBlockSize * cyBlockNumber + 2 * iBorderSL;
	int x12 = x62 + iBorder1;
	int y12 = y62 + iBorder1;
	int x22 = x12 - iBorder1;
	int x41 = x22 - iBorderSL - iBorder2 - cxCounter;
	int y41 = y31;
	int x42 = x22 - iBorderSL - iBorder2;
	int y42 = y32;
	int x51 = x12 / 2 - cyCounter / 2;
	int y51 = y31;
	int x52 = x12 / 2 + cyCounter / 2;
	int y52 = y32;
	cxClientSize = x12;
	cyClientSize = y12;
	RECT rectGlobalBackground{ x11, y11, x12, y12 };
	RECT rectControlBar{ x21, y21, x22, y22 };
	RECT rectFlagCounter{ x31, y31, x32, y32 };
	RECT rectTimeCounter{ x41, y41, x42, y42 };
	RECT rectResetButton{ x51, y51, x52, y52 };
	RECT rectMineField{ x61, y61, x62, y62 };
	GlobalBackground.Reset(rectGlobalBackground, iBorderSL);
	ControlBar.Reset(rectControlBar, iBorderSL);
	FlagCounter.Reset(rectFlagCounter, iBorderSL-2);
	TimeCounter.Reset(rectTimeCounter, iBorderSL-2);
	ResetButton.Reset(rectResetButton, iBorderSL);
	ResetButton.SetMineValue(RESETBUTTON_NORMAL);
	MineField.Reset(rectMineField, iBorderSL);
	bStateFirstClick = true;
	bStateLButtonDown = false;
	bStateRButtonDown = false;
	gamestate = false;
	FlagCounter.SetNumber(iMineNumber);
}


GameManager::~GameManager()
{
}


void GameManager::SetMine(int i, int j)
{
	srand(time(0));

	int iMineCount = 0;
	int cxPos = 0;
	int cyPos = 0;
	while (iMineCount < iMineNumber)
	{
		cxPos = rand() % cxBlockNumber;
		cyPos = rand() % cyBlockNumber;
		if ((i != cxPos) && (j != cyPos) && (MineBlock[cxPos][cyPos].GetMineValue() != MS_MINE))
		{
			MineBlock[cxPos][cyPos].SetMineValue(MS_MINE);
			iMineCount++;
		}
	}
	for (int i = 0; i < cxBlockNumber; i++)
	{
		for (int j = 0; j < cyBlockNumber; j++)
		{
			if (MineBlock[i][j].GetMineValue() != 9)
			{
				MineBlock[i][j].SetMineValue(GetAroundNumber(i, j, MS_MINE));
			}
		}
	}
}


int GameManager::GetAroundNumber(int i, int j, MINESTYLE ms)
{
	
	int iMsNumber = 0;
	if (GetBlockState(i - 1, j - 1, ms))
		iMsNumber++;
	if (GetBlockState(i - 1, j, ms))
		iMsNumber++;
	if (GetBlockState(i - 1, j + 1, ms))
		iMsNumber++;
	if (GetBlockState(i, j - 1, ms))
		iMsNumber++;
	if (GetBlockState(i, j + 1, ms))
		iMsNumber++;
	if (GetBlockState(i + 1, j - 1, ms))
		iMsNumber++;
	if (GetBlockState(i + 1, j, ms))
		iMsNumber++;
	if (GetBlockState(i + 1, j + 1, ms))
		iMsNumber++;
	return iMsNumber;
}


bool GameManager::GetBlockState(int i, int j, MINESTYLE ms)
{
	if (!Exist(i, j))
		return false;
	if (ms == MS_FLAG)
	{
		if (MineBlock[i][j].flagstate == FS_FLAG)
		{
			return true;
		}
		else return false;
	}
	if (MineBlock[i][j].GetMineValue() == ms)
		return true;
	return false;
}


bool GameManager::Judgment()
{
	return gamestate;
}


void GameManager::AutoUncover(const HDC & hdc, int i, int j)
{
	std::stack<POINT> sk;
	POINT pt{ i, j };
	sk.push(pt);
	while (!sk.empty())
	{
		POINT pt = sk.top();
		sk.pop();
		if (GetBlockState(pt.x,pt.y,0))
		{
			POINT pt1;
			pt1.x = pt.x - 1;
			pt1.y = pt.y;
			if (Uncover(hdc, pt1.x, pt1.y))
				sk.push(pt1);
			pt1.x = pt.x - 1;
			pt1.y = pt.y + 1;
			if (Uncover(hdc, pt1.x, pt1.y))
				sk.push(pt1);
			pt1.x = pt.x;
			pt1.y = pt.y + 1;
			if (Uncover(hdc, pt1.x, pt1.y))
				sk.push(pt1);
			pt1.x = pt.x + 1;
			pt1.y = pt.y + 1;
			if (Uncover(hdc, pt1.x, pt1.y))
				sk.push(pt1);
			pt1.x = pt.x + 1;
			pt1.y = pt.y;
			if (Uncover(hdc, pt1.x, pt1.y))
				sk.push(pt1);
			pt1.x = pt.x + 1;
			pt1.y = pt.y - 1;
			if (Uncover(hdc, pt1.x, pt1.y))
				sk.push(pt1);
			pt1.x = pt.x;
			pt1.y = pt.y - 1;
			if (Uncover(hdc, pt1.x, pt1.y))
				sk.push(pt1);
			pt1.x = pt.x - 1;
			pt1.y = pt.y - 1;
			if (Uncover(hdc, pt1.x, pt1.y))
				sk.push(pt1);
		}
	}
	


}


bool GameManager::Uncover(const HDC & hdc, int i, int j)
{
	if (!Controlable(i, j))
		return false;
	/*MineBlock[i][j].OnLButtonDown(hdc);
	MineBlock[i][j].OnLButtonUp(hdc);*/
	LButtonDown(hdc, i, j);
	LButtonUp(hdc, i, j);
	return true;
}


bool GameManager::Controlable(int i, int j)
{
	if (i < 0 || i >= cxBlockNumber || j < 0 || j >= cyBlockNumber || MineBlock[i][j].blockstate || (MineBlock[i][j].flagstate == FS_FLAG))
		return false;
	return true;
}


bool GameManager::Flagable(int i, int j)
{
	if (i < 0 || i >= cxBlockNumber || j < 0 || j >= cyBlockNumber || MineBlock[i][j].blockstate)
		return false;
	return true;
}


bool GameManager::LButtonDown(const HDC & hdc, int i, int j)
{
	if (!Controlable(i, j))
		return false;
	MineBlock[i][j].OnLButtonDown(hdc);
	return true;
}


bool GameManager::PaintBlock(const HDC & hdc, int i, int j)
{
	if (!Controlable(i, j))
		return false;
	MineBlock[i][j].Paint(hdc);
	return true;
}


bool GameManager::LButtonUp(const HDC & hdc, int i, int j)
{
	if (!Controlable(i, j))
		return false;
	MineBlock[i][j].OnLButtonUp(hdc);
	if (MineBlock[i][j].GetMineValue() == MS_MINE)
		gamestate = true;
	AutoUncover(hdc, i, j);
	return true;
}


bool GameManager::RButtonUp(const HDC & hdc, int i, int j)
{
	if (!Flagable(i, j))
		return false;
	MineBlock[i][j].OnRButtonUp(hdc);
	if (MineBlock[i][j].flagstate == FS_FLAG)
	{
		--FlagCounter;
	}
	else if (MineBlock[i][j].flagstate == FS_QUESTIONMARK)
	{
		++FlagCounter;
	}
	FlagCounter.Paint(hdc);
	return true;
}


bool GameManager::Unknown(int i, int j)
{
	if (!MineBlock[i][j].blockstate || (MineBlock[i][j].flagstate == FS_FLAG) || (GetAroundNumber(i, j, MS_FLAG) != MineBlock[i][j].GetMineValue()))
		return true;
	return false;
}


void GameManager::DoubleButtonDown(const HDC & hdc, int i, int j)
{
	LButtonDown(hdc, i - 1, j - 1);
	LButtonDown(hdc, i - 1, j);
	LButtonDown(hdc, i - 1, j + 1);
	LButtonDown(hdc, i, j - 1);
	LButtonDown(hdc, i, j);
	LButtonDown(hdc, i, j + 1);
	LButtonDown(hdc, i + 1, j - 1);
	LButtonDown(hdc, i + 1, j);
	LButtonDown(hdc, i + 1, j + 1);
}


void GameManager::DoubleButtonUp(const HDC & hdc, int i, int j)
{
	if (Unknown(i,j))
	{
		PaintBlock(hdc, i - 1, j - 1);
		PaintBlock(hdc, i - 1, j);
		PaintBlock(hdc, i - 1, j + 1);
		PaintBlock(hdc, i, j - 1);
		PaintBlock(hdc, i, j);
		PaintBlock(hdc, i, j + 1);
		PaintBlock(hdc, i + 1, j - 1);
		PaintBlock(hdc, i + 1, j);
		PaintBlock(hdc, i + 1, j + 1);
		return;
	}
	else
	{
		LButtonUp(hdc, i - 1, j - 1);
		LButtonUp(hdc, i - 1, j);
		LButtonUp(hdc, i - 1, j + 1);
		LButtonUp(hdc, i, j - 1);
		LButtonUp(hdc, i, j);
		LButtonUp(hdc, i, j + 1);
		LButtonUp(hdc, i + 1, j - 1);
		LButtonUp(hdc, i + 1, j);
		LButtonUp(hdc, i + 1, j + 1);
		return;
	}
}


void GameManager::DoubleButtonRecover(const HDC & hdc, int i, int j)
{
	PaintBlock(hdc, i - 1, j - 1);
	PaintBlock(hdc, i - 1, j);
	PaintBlock(hdc, i - 1, j + 1);
	PaintBlock(hdc, i, j - 1);
	PaintBlock(hdc, i, j);
	PaintBlock(hdc, i, j + 1);
	PaintBlock(hdc, i + 1, j - 1);
	PaintBlock(hdc, i + 1, j);
	PaintBlock(hdc, i + 1, j + 1);
}



bool GameManager::Exist(int i, int j)
{
	if (i < 0 || i >= cxBlockNumber || j < 0 || j >= cyBlockNumber)
		return false;
	return true;
}


void GameManager::GameOver(const HWND & hWnd, const HDC & hdc)
{
	TimeCounter.Stop(hWnd);
	for (int i = 0; i < cxBlockNumber; i++)
	{
		for (int j = 0; j < cyBlockNumber; j++)
		{
			if (MineBlock[i][j].GetMineValue() == MS_MINE)
			{
				MineBlock[i][j].PaintMine(hdc);
			}
			MineBlock[i][j].PaintError(hdc);
			MineBlock[i][j].blockstate = true;
		}
	}
	//ÓÎÏ·½áÊø
}


void GameManager::Reset(const HWND & hWnd, PRECT lprect)
{
	if (!bStateFirstClick)
	{
		TimeCounter.Stop(hWnd);
	}

	cxBlockNumber = 30;
	cyBlockNumber = 16;
	iMineNumber = 99;
	int x11 = 0, y11 = 0;
	int x21 = x11 + iBorder1;
	int y21 = y11 + iBorder1;
	int x31 = x21 + iBorderSL + iBorder2;
	int y31 = y21 + iBorderSL + iBorder2;
	int x32 = x31 + cxCounter;
	int y32 = y31 + cyCounter;
	int y22 = 2 * (iBorderSL + iBorder2) + cyCounter + iBorder1;
	int x61 = x21;
	int y61 = y22 + iBorder1;
	int x71[30][16], y71[30][16];
	int x72[30][16], y72[30][16];
	for (int i = 0; i < cxBlockNumber; i++)
	{
		for (int j = 0; j < cyBlockNumber; j++)
		{
			x71[i][j] = x61 + iBorderSL + i * cxBlockSize;
			y71[i][j] = y61 + iBorderSL + j*cyBlockSize;
			x72[i][j] = x71[i][j] + cxBlockSize;
			y72[i][j] = y71[i][j] + cyBlockSize;
			RECT rectMineBlock{ x71[i][j], y71[i][j], x72[i][j], y72[i][j] };
			MineBlock[i][j].Reset(rectMineBlock, iBorderSL);

		}
	}
	int x62 = x61 + cxBlockSize * cxBlockNumber + 2 * iBorderSL;
	int y62 = y61 + cyBlockSize * cyBlockNumber + 2 * iBorderSL;
	int x12 = x62 + iBorder1;
	int y12 = y62 + iBorder1;
	int x22 = x12 - iBorder1;
	int x41 = x22 - iBorderSL - iBorder2 - cxCounter;
	int y41 = y31;
	int x42 = x22 - iBorderSL - iBorder2;
	int y42 = y32;
	int x51 = x12 / 2 - cyCounter / 2;
	int y51 = y31;
	int x52 = x12 / 2 + cyCounter / 2;
	int y52 = y32;
	cxClientSize = x12;
	cyClientSize = y12;
	RECT rectGlobalBackground{ x11, y11, x12, y12 };
	RECT rectControlBar{ x21, y21, x22, y22 };
	RECT rectFlagCounter{ x31, y31, x32, y32 };
	RECT rectTimeCounter{ x41, y41, x42, y42 };
	RECT rectResetButton{ x51, y51, x52, y52 };
	RECT rectMineField{ x61, y61, x62, y62 };
	GlobalBackground.Reset(rectGlobalBackground, iBorderSL);
	ControlBar.Reset(rectControlBar, iBorderSL);
	FlagCounter.Reset(rectFlagCounter, iBorderSL - 2);
	TimeCounter.Reset(rectTimeCounter, iBorderSL - 2);
	ResetButton.Reset(rectResetButton, iBorderSL);
	ResetButton.SetMineValue(RESETBUTTON_NORMAL);
	MineField.Reset(rectMineField, iBorderSL);
	bStateFirstClick = true;
	bStateLButtonDown = false;
	bStateRButtonDown = false;
	gamestate = false;
	FlagCounter.SetNumber(iMineNumber);
	InvalidateRect(hWnd, lprect, FALSE);
}
