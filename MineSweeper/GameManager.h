#pragma once

#include <stack>
class GameManager
{
	const int iBorder1 = 12;
	const int iBorder2 = 8;
	const int iBorderSL = 4;
	const int cyCounter = 40;
	const int cxCounter = cyCounter / 2 * 3;
	const int cxBlockSize = 30;
	const int cyBlockSize = 30;

	
public:
	Box GlobalBackground;
	Field ControlBar;
	Counter FlagCounter;
	Counter TimeCounter;
	Block ResetButton;
	Field MineField;
	Block MineBlock[30][16];
	
	bool bStateFirstClick;
	bool bStateLButtonDown;
	bool bStateRButtonDown;

	int iMineNumber;
	int cxBlockNumber;
	int cyBlockNumber;
	int cxClientSize;
	int cyClientSize;
	
public:
	GameManager();
	~GameManager();
	void SetMine(int i, int j);
	int GetAroundNumber(int i, int j, MINESTYLE ms);//获取周围块ms的数量
	bool GetBlockState(int i, int j, MINESTYLE ms);//获取块是否为ms
	bool Judgment();//判断输赢
	void AutoUncover(const HDC & hdc, int i, int j);//自动掀开
	bool Uncover(const HDC & hdc, int i, int j);//掀开
	bool Controlable(int i, int j);//判断是否可控制
	void DoubleButtonDown(const HDC & hdc, int i, int j);
	void DoubleButtonUp(const HDC & hdc, int i, int j);
	bool LButtonDown(const HDC & hdc, int i, int j);
	bool PaintBlock(const HDC & hdc, int i, int j);
	bool LButtonUp(const HDC & hdc, int i, int j);
	bool RButtonUp(const HDC & hdc, int i, int j);
	
	void DoubleButtonRecover(const HDC & hdc, int i, int j);
	bool Flagable(int i, int j);
	bool Unknown(int i, int j);
	bool Exist(int i, int j);
	bool gamestate;
	void GameOver(const HWND & hWnd, const HDC & hdc);
	void Reset(const HWND & hWnd, PRECT lprect);
};

