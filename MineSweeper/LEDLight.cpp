#include "stdafx.h"
#include "LEDLight.h"

HBRUSH LEDLight::hbrLightOn = CreateSolidBrush(CR_COUNTER_LIGHT_ON);
HBRUSH LEDLight::hbrLightOff = CreateSolidBrush(CR_COUNTER_LIGHT_OFF);
LEDLight::LEDLight(const RECT & rect, const int & iLightNum)
{
	Init(rect, iLightNum);
}
LEDLight::LEDLight()
{
}

LEDLight::~LEDLight()
{
	DeleteObject(hbrLightOn);
	DeleteObject(hbrLightOff);
}
void LEDLight::Init(const RECT & rect, const int & iLightNum)
{
	Size = rect;
	Set(iLightNum);
	SetOff();
}
void LEDLight::Set(const int & iLightNum)
{
	switch (iLightNum)
	{
	case 0:
		Set0();
		break;
	case 1:
		Set1();
		break;
	case 2:
		Set2();
		break;
	case 3:
		Set3();
		break;
	case 4:
		Set4();
		break;
	case 5:
		Set5();
		break;
	case 6:
		Set6();
		break;
	default:
		break;
	}
}
void LEDLight::Set0()
{
	LONG dx = Size.right - Size.left;
	LONG dy = Size.bottom - Size.top;
	aptShape[0] = { Size.left + dx * LED_X1, Size.top + dy * LED_Y1 };//A
	aptShape[1] = { Size.left + dx * LED_X1, Size.top + dy * LED_Y4 };//B
	aptShape[2] = { Size.left + dx * LED_X2, Size.top + dy * LED_Y3 };//C
	aptShape[3] = { Size.left + dx * LED_X2, Size.top + dy * LED_Y2 };//D
	iPointNum = 4;
}
void LEDLight::Set1()
{
	LONG dx = Size.right - Size.left;
	LONG dy = Size.bottom - Size.top;
	aptShape[0] = { Size.left + dx * LED_X1, Size.top + dy * LED_Y4 };//B
	aptShape[1] = { Size.left + dx * LED_X2, Size.top + dy * LED_Y3 };//C
	aptShape[2] = { Size.right - dx * LED_X2, Size.top + dy * LED_Y3 };//E
	aptShape[3] = { Size.right - dx * LED_X1, Size.top + dy * LED_Y4 };//F
	aptShape[4] = { Size.right - dx * LED_X2, Size.bottom - dy * LED_Y3 };//G
	aptShape[5] = { Size.left + dx * LED_X2, Size.bottom - dy * LED_Y3 };//H
	iPointNum = 6;
}
void LEDLight::Set2()
{
	LONG dx = Size.right - Size.left;
	LONG dy = Size.bottom - Size.top;
	aptShape[0] = { Size.right - dx * LED_X1, Size.top + dy * LED_Y4 };//F
	aptShape[1] = { Size.right - dx * LED_X2, Size.bottom - dy * LED_Y3 };//G
	aptShape[2] = { Size.right - dx * LED_X2, Size.bottom - dy * LED_Y2 };//I
	aptShape[3] = { Size.right - dx * LED_X1, Size.bottom - dy * LED_Y1 };//J
	iPointNum = 4;
}
void LEDLight::Set3()
{
	LONG dx = Size.right - Size.left;
	LONG dy = Size.bottom - Size.top;
	aptShape[0] = { Size.right - dx * LED_X2, Size.bottom - dy * LED_Y2 };//I
	aptShape[1] = { Size.right - dx * LED_X1, Size.bottom - dy * LED_Y1 };//J
	aptShape[2] = { Size.left + dx * LED_X1, Size.bottom - dy * LED_Y1 };//K
	aptShape[3] = { Size.left + dx * LED_X2, Size.bottom - dy * LED_Y2 };//L
	iPointNum = 4;
}
void LEDLight::Set4()
{
	LONG dx = Size.right - Size.left;
	LONG dy = Size.bottom - Size.top;
	aptShape[0] = { Size.left + dx * LED_X1, Size.bottom - dy * LED_Y1 };//K
	aptShape[1] = { Size.left + dx * LED_X2, Size.bottom - dy * LED_Y2 };//L
	aptShape[2] = { Size.left + dx * LED_X2, Size.bottom - dy * LED_Y3 };//H
	aptShape[3] = { Size.left + dx * LED_X1, Size.top + dy * LED_Y4 };//B
	iPointNum = 4;
}
void LEDLight::Set5()
{
	LONG dx = Size.right - Size.left;
	LONG dy = Size.bottom - Size.top;
	aptShape[0] = { Size.right - dx * LED_X2, Size.top + dy * LED_Y3 };//E
	aptShape[1] = { Size.right - dx * LED_X1, Size.top + dy * LED_Y4 };//F
	aptShape[2] = { Size.right - dx * LED_X1, Size.top + dy * LED_Y1 };//M
	aptShape[3] = { Size.right - dx * LED_X2, Size.top + dy * LED_Y2 };//N
	iPointNum = 4;
}
void LEDLight::Set6()
{
	LONG dx = Size.right - Size.left;
	LONG dy = Size.bottom - Size.top;
	aptShape[0] = { Size.left + dx * LED_X1, Size.top + dy * LED_Y1 };
	aptShape[1] = { Size.right - dx * LED_X1, Size.top + dy * LED_Y1 };
	aptShape[2] = { Size.right - dx * LED_X2, Size.top + dy * LED_Y2 };
	aptShape[3] = { Size.left + dx * LED_X2, Size.top + dy * LED_Y2 };
	iPointNum = 4;
}
void LEDLight::Paint(const HDC & hdc)
{
	int nSavedDC = SaveDC(hdc);
	if (bState)
		SelectObject(hdc, hbrLightOn);
	else
		SelectObject(hdc, hbrLightOff);
	Polygon(hdc, aptShape, iPointNum);
	RestoreDC(hdc, nSavedDC);
}
void LEDLight::SetOn()
{
	bState = true;
}
void LEDLight::SetOff()
{
	bState = false;
}