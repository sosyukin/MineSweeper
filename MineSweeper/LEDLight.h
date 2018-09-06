#pragma once

#define LED_X1 1/10
#define LED_X2 3/10
#define LED_Y1 1/20
#define LED_Y2 1/8
#define LED_Y3 9/20
#define LED_Y4 1/2

class LEDLight
{
	POINT aptShape[6];
	int iPointNum;
	bool bState;
	int iLightNum;
	RECT Size;
	void Set0();
	void Set1();
	void Set2();
	void Set3();
	void Set4();
	void Set5();
	void Set6();

	static HBRUSH hbrLightOn;
	static HBRUSH hbrLightOff;
public:
	LEDLight(const RECT & rect, const int & iLightNum);
	LEDLight();
	~LEDLight();
	void Init(const RECT & rect, const int & iLightNum);
	void Set(const int & iLightNum);
	void SetOn();
	void SetOff();
	void Paint(const HDC & hdc);
};

