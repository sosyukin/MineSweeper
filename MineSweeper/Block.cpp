#include "stdafx.h"
#include "Block.h"


Block::Block(const RECT & rect, const int & width) : Box(rect, width)
{
	Init(rect, width);
}
Block::~Block()
{
}
void Block::Init(const RECT & rect, const int & width)
{
	Box::Init(rect, width);
	InitMineValue();
	flagstate = FS_NULL;
	blockstate = false;
	lf.lfHeight = rect.bottom - rect.top - 10;
	lf.lfWidth = (rect.right - rect.left - 10) * 2 / 3;
	lf.lfWeight = 700;
	lf.lfEscapement = 0;//角度
	lf.lfItalic = FALSE;//斜体
	lf.lfUnderline = FALSE;//下划线
	lf.lfStrikeOut = FALSE;//删除线
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
}
void Block::Reset(const RECT & rect, const int & width)
{
	Box::Reset(rect, width);
	InitMineValue();
	flagstate = FS_NULL;
	blockstate = false;
	lf.lfHeight = rect.bottom - rect.top - 10;
	lf.lfWidth = (rect.right - rect.left - 10) * 2 / 3;
	lf.lfWeight = 700;
	lf.lfEscapement = 0;//角度
	lf.lfItalic = FALSE;//斜体
	lf.lfUnderline = FALSE;//下划线
	lf.lfStrikeOut = FALSE;//删除线
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
}
void Block::InitMineValue()
{
	value = 0;
}
void Block::SetMineValue(int mine)
{
	value = mine;
}
int Block::GetMineValue()
{
	return value;
}
void Block::Paint(const HDC & hdc)
{
	Box::Paint(hdc, hbrSurface);
	PaintBorder(hdc);
	if (value == RESETBUTTON_NORMAL)
		PaintFace(hdc);
}
void Block::PaintBorder(const HDC & hdc)
{
	FillRgn(hdc, hrgnRightBottom, hbrShadow);
	FillRgn(hdc, hrgnLeftTop, hbrLight);
}

void Block::OnLButtonDown(const HDC & hdc)
{
	RECT smRect{ rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1 };
	FillRect(hdc, &rect, hbrShadow);
	FillRect(hdc, &smRect, hbrBackGround);
}
bool Block::OnLButtonUp(const HDC & hdc)
{
	blockstate = true;
	
	if (value != 0)
	{
		RECT smRect{ rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1 };
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
		int nSavedDC = SaveDC(hdc);
		hf = CreateFontIndirect(&lf);
		SelectObject(hdc, hf);
		SetBkColor(hdc, CR_BACKGROUND);
		switch (value)
		{
		case 1:
			SetTextColor(hdc, CR_MINENUM_1);
			break;
		case 2:
			SetTextColor(hdc, CR_MINENUM_2);
			break;
		case 3:
			SetTextColor(hdc, CR_MINENUM_3);
			break;
		case 4:
			SetTextColor(hdc, CR_MINENUM_4);
			break;
		case 5:
			SetTextColor(hdc, CR_MINENUM_5);
			break;
		case 6:
			SetTextColor(hdc, CR_MINENUM_6);
			break;
		case 7:
			SetTextColor(hdc, CR_MINENUM_7);
			break;
		case 8:
			SetTextColor(hdc, CR_MINENUM_8);
			break;
		case 9:
			FillRect(hdc, &rect, hbrShadow);
			FillRect(hdc, &smRect, hBrush);
			SetBkColor(hdc, CR_COUNTER_LIGHT_ON);
			break;
		default:
			break;
		}
		TCHAR szBuffer[5];
		switch (value)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			wsprintf(szBuffer, TEXT("%d"), value);
			break;
		case 9:
			wsprintf(szBuffer, TEXT("M"));
		default:
			break;
		}
		DrawText(hdc, szBuffer, -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		DeleteObject(hf);
		DeleteObject(hBrush);
		RestoreDC(hdc, nSavedDC);
	}
	if (value == 0)
		return true;
	return false;
}
void Block::OnRButtonUp(const HDC & hdc)
{
	int nSavedDC = SaveDC(hdc);
	hf = CreateFontIndirect(&lf);
	SelectObject(hdc, hf);
	SetBkColor(hdc, CR_BACKGROUND);
	TCHAR szBuffer[5];
	switch (flagstate)
	{
	case FS_NULL:
		wsprintf(szBuffer, TEXT("F"));
		flagstate = FS_FLAG;
		DrawText(hdc, szBuffer, -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		break;
	case FS_FLAG:
		wsprintf(szBuffer, TEXT("?"));
		flagstate = FS_QUESTIONMARK;
		DrawText(hdc, szBuffer, -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		break;
	case FS_QUESTIONMARK:
		Paint(hdc);
		flagstate = FS_NULL;
		break;
	default:
		break;
	}
	DeleteObject(hf);
	RestoreDC(hdc, nSavedDC);
}
void Block::OnLRButtonDown(const HDC & hdc)
{
	
}
void Block::OnLRButtonUp(const HDC & hdc)
{

}

void Block::PaintMine(const HDC & hdc)
{
	if (!blockstate)
	{
		int nSavedDC = SaveDC(hdc);
		RECT smRect{ rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1 };
		FillRect(hdc, &rect, hbrShadow);
		FillRect(hdc, &smRect, hbrBackGround);
		
		hf = CreateFontIndirect(&lf);
		SelectObject(hdc, hf);

		SetBkColor(hdc, CR_BACKGROUND);
		TCHAR szBuffer[5];
		wsprintf(szBuffer, TEXT("M"));
		DrawText(hdc, szBuffer, -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

		DeleteObject(hf);
		RestoreDC(hdc, nSavedDC);
	}
	
}


void Block::PaintError(const HDC & hdc)
{
	if (flagstate && (value != MS_MINE))
	{
		int nSavedDC = SaveDC(hdc);
		RECT smRect{ rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1 };
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));

		FillRect(hdc, &rect, hbrShadow);
		FillRect(hdc, &smRect, hbrBackGround);
		
		hf = CreateFontIndirect(&lf);
		SelectObject(hdc, hf);
		SetBkColor(hdc, CR_BACKGROUND);
		TCHAR szBuffer[5];
		wsprintf(szBuffer, TEXT("M"));
		DrawText(hdc, szBuffer, -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		SelectObject(hdc, hPen);
		MoveToEx(hdc, rect.left + 2, rect.top + 2, NULL);
		LineTo(hdc, rect.right - 2, rect.bottom - 2);
		MoveToEx(hdc, rect.right - 2, rect.top + 2, NULL);
		LineTo(hdc, rect.left + 2, rect.bottom - 2);

		DeleteObject(hf);
		DeleteObject(hPen);
		RestoreDC(hdc, nSavedDC);
	}
		
}


void Block::PaintFace(const HDC & hdc)
{
	int nSavedDC = SaveDC(hdc);
	int cxCenter = (rect.right - rect.left) / 2;
	int cyCenter = (rect.bottom - rect.top) / 2;
	POINT apt[4] = {
		rect.left + cxCenter - 1.5 * m_width, rect.top + cyCenter + m_width,
		rect.left + cxCenter - m_width, rect.top + cyCenter + 2 * m_width,
		rect.right - cxCenter + m_width, rect.top + cyCenter + 2 * m_width,
		rect.right - cxCenter + 1.5 * m_width, rect.top + cyCenter + m_width
	};
	HBRUSH hbrYellow = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH hbrBlack = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hbrYellow);
	Ellipse(hdc, rect.left + 2 * m_width, rect.top + 2 * m_width, rect.right - 2 * m_width, rect.bottom - 2 * m_width);
	SelectObject(hdc, hbrBlack);
	
	Ellipse(hdc, rect.left + cxCenter - 1.5 * m_width, rect.top + cyCenter - m_width, rect.right - cxCenter - 0.5 * m_width, rect.bottom - cyCenter);
	Ellipse(hdc, rect.left + cxCenter + 0.5 * m_width, rect.top + cyCenter - m_width, rect.right - cxCenter + 1.5 * m_width, rect.bottom - cyCenter);
	PolyBezier(hdc, apt, 4);
	DeleteObject(hbrYellow);
	DeleteObject(hbrBlack);
	RestoreDC(hdc, nSavedDC);
}
