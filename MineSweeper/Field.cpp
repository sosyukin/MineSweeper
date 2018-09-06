#include "stdafx.h"
#include "Field.h"


Field::Field(const RECT & rect,const int & width) :Box(rect, width)
{
}

Field::~Field()
{
}

void Field::Paint(const HDC & hdc)
{
	Box::Paint(hdc, hbrBackGround);
	PaintBorder(hdc);
}

void Field::PaintBorder(const HDC & hdc)
{
	FillRgn(hdc, hrgnLeftTop, hbrShadow);
	FillRgn(hdc, hrgnRightBottom, hbrLight);
}
