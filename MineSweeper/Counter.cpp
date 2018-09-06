#include "stdafx.h"
#include "Counter.h"

#define ID_TIMER 1
Counter::Counter(const RECT & rect) :Field(rect, 2)
{
	Init(rect);
}

Counter::~Counter()
{
}
void Counter::Paint(const HDC & hdc)
{
	Box::Paint(hdc, hbrBlack);
	Field::PaintBorder(hdc);
	for (size_t i = 0; i < PANEL_NUM; i++)
	{
		NumPanel[i].Paint(hdc);
	}
}
void Counter::Start(const HWND & hWnd)
{
	GetLocalTime(&m_StartTime);
	state = true;
	SetTimer(hWnd, ID_TIMER, 500, NULL);
	
}
void Counter::Refresh(const HDC & hdc)
{
	SYSTEMTIME newsystime;
	GetLocalTime(&newsystime);
	m_CounterNumber = newsystime.wSecond - m_StartTime.wSecond;
	m_CounterNumber += (newsystime.wMinute - m_StartTime.wMinute) * 60;
	
	SetNumber(m_CounterNumber);
	Paint(hdc);
}
int Counter::Stop(const HWND & hWnd)
{
	KillTimer(hWnd, ID_TIMER);
	return m_CounterNumber;
}
void Counter::Reset(const RECT & rect, const int width)
{
	Field::Reset(rect, width);
	RECT trect = rect;
	trect.bottom -= width;
	trect.left += width;
	trect.right -= width;
	trect.top += width;

	for (size_t i = 0; i < PANEL_NUM; i++)
	{
		RECT t1 = trect;
		t1.left += i * (trect.right - trect.left) / 3;
		t1.right = trect.left + (i + 1) * (trect.right - trect.left) / 3;
		NumPanel[i].SetRect(t1);
	}
	state = false;
}
void Counter::Init(const RECT & rect, const int & width)
{
	Field::Init(rect, width);
	RECT trect = rect;
	trect.bottom -= width;
	trect.left += width;
	trect.right -= width;
	trect.top += width;
	
	for (size_t i = 0; i < PANEL_NUM; i++)
	{
		RECT t1 = trect;
		t1.left += i * (trect.right - trect.left) / 3;
		t1.right = trect.left + (i + 1) * (trect.right - trect.left) / 3;
		NumPanel[i].SetRect(t1);
	}
	state = false;
}
void Counter::SetNumber(int number)
{
	if (number >= 0)
	{
		m_CounterNumber = number % 1000;
		for (size_t i = 0; i < PANEL_NUM; i++)
		{
			NumPanel[PANEL_NUM - i - 1].SetNum(number % 10);
			number /= 10;
		}
	}
	else
	{
		m_CounterNumber = number % 1000;
		for (size_t i = 0; i < PANEL_NUM - 1; i++)
		{
			NumPanel[PANEL_NUM - i - 1].SetNum(number % 10);
			number /= 10;
		}
		NumPanel[0].SetValue('-');
	}
	
}
Counter & Counter::operator++()
{
	SetNumber(++m_CounterNumber);
	return *this;
}
Counter & Counter::operator--()
{
	SetNumber(--m_CounterNumber);
	return *this;
}