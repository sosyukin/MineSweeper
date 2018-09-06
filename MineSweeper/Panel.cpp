#include "stdafx.h"
#include "Panel.h"


Panel::Panel(const RECT & rect)
{
	SetRect(rect);
}

Panel::~Panel()
{
}

void Panel::SetRect(const RECT & rect)
{
	for (size_t i = 0; i < LED_NUM; i++)
	{
		m_LEDLight[i].Init(rect, i);
	}
	SetNum(0);
}

void Panel::SetNum(const int & num)
{
	switch (num)
	{
	case 0:
		Set_0();
		break;
	case 1:
		Set_1();
		break;
	case 2:
		Set_2();
		break;
	case 3:
		Set_3();
		break;
	case 4:
		Set_4();
		break;
	case 5:
		Set_5();
		break;
	case 6:
		Set_6();
		break;
	case 7:
		Set_7();
		break;
	case 8:
		Set_8();
		break;
	case 9:
		Set_9();
		break;
	default:
		break;
	}
}
void Panel::Set_0()
{
	m_LEDLight[0].SetOn();
	m_LEDLight[1].SetOff();
	m_LEDLight[2].SetOn();
	m_LEDLight[3].SetOn();
	m_LEDLight[4].SetOn();
	m_LEDLight[5].SetOn();
	m_LEDLight[6].SetOn();
}
void Panel::Set_1()
{
	m_LEDLight[0].SetOff();
	m_LEDLight[1].SetOff();
	m_LEDLight[2].SetOn();
	m_LEDLight[3].SetOff();
	m_LEDLight[4].SetOff();
	m_LEDLight[5].SetOn();
	m_LEDLight[6].SetOff();
}
void Panel::Set_2()
{
	m_LEDLight[0].SetOff();
	m_LEDLight[1].SetOn();
	m_LEDLight[2].SetOff();
	m_LEDLight[3].SetOn();
	m_LEDLight[4].SetOn();
	m_LEDLight[5].SetOn();
	m_LEDLight[6].SetOn();
}
void Panel::Set_3()
{
	m_LEDLight[0].SetOff();
	m_LEDLight[1].SetOn();
	m_LEDLight[2].SetOn();
	m_LEDLight[3].SetOn();
	m_LEDLight[4].SetOff();
	m_LEDLight[5].SetOn();
	m_LEDLight[6].SetOn();
}
void Panel::Set_4()
{
	m_LEDLight[0].SetOn();
	m_LEDLight[1].SetOn();
	m_LEDLight[2].SetOn();
	m_LEDLight[3].SetOff();
	m_LEDLight[4].SetOff();
	m_LEDLight[5].SetOn();
	m_LEDLight[6].SetOff();
}
void Panel::Set_5()
{
	m_LEDLight[0].SetOn();
	m_LEDLight[1].SetOn();
	m_LEDLight[2].SetOn();
	m_LEDLight[3].SetOn();
	m_LEDLight[4].SetOff();
	m_LEDLight[5].SetOff();
	m_LEDLight[6].SetOn();
}
void Panel::Set_6()
{
	m_LEDLight[0].SetOn();
	m_LEDLight[1].SetOn();
	m_LEDLight[2].SetOn();
	m_LEDLight[3].SetOn();
	m_LEDLight[4].SetOn();
	m_LEDLight[5].SetOff();
	m_LEDLight[6].SetOn();
}
void Panel::Set_7()
{
	m_LEDLight[0].SetOff();
	m_LEDLight[1].SetOff();
	m_LEDLight[2].SetOn();
	m_LEDLight[3].SetOff();
	m_LEDLight[4].SetOff();
	m_LEDLight[5].SetOn();
	m_LEDLight[6].SetOn();
}
void Panel::Set_8()
{
	m_LEDLight[0].SetOn();
	m_LEDLight[1].SetOn();
	m_LEDLight[2].SetOn();
	m_LEDLight[3].SetOn();
	m_LEDLight[4].SetOn();
	m_LEDLight[5].SetOn();
	m_LEDLight[6].SetOn();
}
void Panel::Set_9()
{
	m_LEDLight[0].SetOn();
	m_LEDLight[1].SetOn();
	m_LEDLight[2].SetOn();
	m_LEDLight[3].SetOn();
	m_LEDLight[4].SetOff();
	m_LEDLight[5].SetOn();
	m_LEDLight[6].SetOn();
}
void Panel::Paint(const HDC & hdc)
{
	for (size_t i = 0; i < LED_NUM; i++)
	{
		m_LEDLight[i].Paint(hdc);
	}
}
void Panel::SetValue(const char & value)
{
	switch (value)
	{
	case '-':
		Set_centerline();
		break;
	default:
		break;
	}
}
void Panel::Set_centerline()
{
	m_LEDLight[0].SetOff();
	m_LEDLight[1].SetOn();
	m_LEDLight[2].SetOff();
	m_LEDLight[3].SetOff();
	m_LEDLight[4].SetOff();
	m_LEDLight[5].SetOff();
	m_LEDLight[6].SetOff();
}