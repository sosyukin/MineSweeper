#pragma once
#define LED_NUM 7
class Panel
{
	LEDLight m_LEDLight[LED_NUM];

private:
	void Set_0();
	void Set_1();
	void Set_2();
	void Set_3();
	void Set_4();
	void Set_5();
	void Set_6();
	void Set_7();
	void Set_8();
	void Set_9();
	void Set_centerline();
public:
	Panel(const RECT & rect = RECT());
	~Panel();
	void SetRect(const RECT & rect);
	void SetNum(const int & num);
	void SetValue(const char & value);
	void Paint(const HDC & hdc);
};

