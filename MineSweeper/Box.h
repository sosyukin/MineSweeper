#pragma once

//we can paint background color, but not height border
//Bug: static hbrush can not ~Îö¹¹
class Box
{
private:
	
protected:
	
	static HBRUSH hbrSurface;
	static HBRUSH hbrLight;
	static HBRUSH hbrShadow;
	static HBRUSH hbrBackGround;
	static HBRUSH hbrBlack;
	
	//Skip
	HRGN hrgnLeftTop;
	HRGN hrgnRightBottom;
	int m_width;
	
public:
	Box(const RECT & rect = RECT(), const int & width = 4);//Init rect and height width
	~Box();
	RECT rect;
	void Init(const RECT & rect, const int & width = 4);//Init rect and height width
	void Paint(const HDC & hdc, const HBRUSH & hBrush = hbrSurface);//Paint rect but not height border
	void Reset(const RECT & rect, const int & width = 4);
	bool isIn(int cxPos, int cyPos);
};

