#pragma once
#include "Box.h"
class Block :
	public Box
{
public:
	Block(const RECT & rect = RECT(), const int & width = 4);
	~Block();

	void Paint(const HDC & hdc);
	void InitMineValue();
	void SetMineValue(int mine);
	int GetMineValue();
	void Init(const RECT & rect, const int & width);
	void Reset(const RECT & rect, const int & width = 4);

	bool blockstate;
	int flagstate;
protected:
	void PaintBorder(const HDC & hdc);
	int value;
	

	HFONT hf;
	LOGFONT lf;
public:
	void OnLButtonDown(const HDC & hdc);
	bool OnLButtonUp(const HDC & hdc);
	void OnRButtonUp(const HDC & hdc);
	void OnLRButtonDown(const HDC & hdc);
	void OnLRButtonUp(const HDC & hdc);
	void PaintMine(const HDC & hdc);
	void PaintError(const HDC & hdc);
	void PaintFace(const HDC & hdc);
};

