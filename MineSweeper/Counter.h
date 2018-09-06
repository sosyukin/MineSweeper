#pragma once
#include "Box.h"

#define PANEL_NUM 3
class Counter :
	public Field
{
public:
	Counter(const RECT & rect = RECT());
	~Counter();
	void Reset(const RECT & rect = RECT(), const int width = 2);
	void SetNumber(int number);
	Counter & operator++();
	Counter & operator--();
	void Start(const HWND & hWnd);
	void Refresh(const HDC & hdc);
	int Stop(const HWND & hWnd);
protected:
	bool state;
	int m_CounterNumber;
	Panel NumPanel[PANEL_NUM];
	SYSTEMTIME m_StartTime;
	
public:
	void Paint(const HDC & hdc);
	void Init(const RECT & rect, const int & width = 2);
};

