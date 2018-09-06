#include "stdafx.h"
#include "Box.h"


HBRUSH Box::hbrSurface = CreateSolidBrush(CR_SURFACE);
HBRUSH Box::hbrLight = CreateSolidBrush(CR_LIGHT);
HBRUSH Box::hbrShadow = CreateSolidBrush(CR_SHADOW);
HBRUSH Box::hbrBackGround = CreateSolidBrush(CR_BACKGROUND);
HBRUSH Box::hbrBlack = CreateSolidBrush(CR_COUNTER_BG);


Box::Box(const RECT & rect, const int & width)
{
	
	Init(rect, width);

	
}


Box::~Box()
{
	DeleteObject(hbrSurface);
	DeleteObject(hbrLight);
	DeleteObject(hbrShadow);
	DeleteObject(hbrBackGround);
	DeleteObject(hbrBlack);
	DeleteObject(hrgnLeftTop);
	DeleteObject(hrgnRightBottom);
}

void Box::Init(const RECT & rect, const int & width)
{
	this->rect = rect;
	POINT apt1[6] = {
		this->rect.left, this->rect.top,
		this->rect.right, this->rect.top,
		this->rect.right - width, this->rect.top + width,
		this->rect.left + width, this->rect.top + width,
		this->rect.left + width, this->rect.bottom - width,
		this->rect.left, this->rect.bottom };
	POINT apt2[6] = {
		this->rect.right, this->rect.bottom,
		this->rect.left, this->rect.bottom,
		this->rect.left + width, this->rect.bottom - width,
		this->rect.right - width, this->rect.bottom - width,
		this->rect.right - width, this->rect.top + width,
		this->rect.right, this->rect.top };
	hrgnLeftTop = CreatePolygonRgn(apt1, 6, WINDING);
	hrgnRightBottom = CreatePolygonRgn(apt2, 6, WINDING);
	m_width = width;
}
void Box::Paint(const HDC & hdc, const HBRUSH & hBrush)
{
	FillRect(hdc, &rect, hBrush);
}

void Box::Reset(const RECT & rect, const int & width)
{
	DeleteObject(hrgnLeftTop);
	DeleteObject(hrgnRightBottom);
	Init(rect, width);
}


bool Box::isIn(int cxPos, int cyPos)
{
	if ((cxPos > rect.left)&&(cxPos < rect.right)&&(cyPos > rect.top)&&(cyPos < rect.bottom))
	{
		return true;
	}
	else return false;
}
