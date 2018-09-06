#pragma once
#include "Box.h"

//define how to paint border
class Field :
	public Box
{
public:
	Field(const RECT & rect = RECT(), const int & width = 4);
	~Field();

	void Paint(const HDC & hdc);
protected:
	void PaintBorder(const HDC & hdc);
};