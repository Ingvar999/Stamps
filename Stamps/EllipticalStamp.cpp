#include "EllipticalStamp.h"

#include <math.h>
#include <strsafe.h>

void EllipticalStamp::Print(POINT position)
{
	size_t textLength = wcslen(text);
	INT charWidth = (INT)ceil((double)(radius.x + radius.y) / textLength);

	INT k = 0;
	FLOAT angle = Pi;
	FLOAT delta = 2 * Pi / textLength;

	HDC sourceDC = CreateCompatibleDC(destDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(destDC, 0, 0);
	HBITMAP oldbmp = (HBITMAP)SelectObject(sourceDC, hBitmap);

	PLOGFONT pLogFont = (PLOGFONT)LocalAlloc(LPTR, sizeof(LOGFONT));
	pLogFont->lfPitchAndFamily = family;
	//StringCchCopy(pLogFont->lfFaceName, wcslen(font), (STRSAFE_LPSTR)font);
	pLogFont->lfWeight = FW_NORMAL;
	pLogFont->lfHeight = 3 * charWidth;
	pLogFont->lfWidth = charWidth;
	HFONT hFont = CreateFontIndirect(pLogFont);
	HGDIOBJ hFontPrev = SelectObject(sourceDC, hFont);
	for (INT i = 0; k < textLength; angle += delta, ++i)
	{
		RECT rect;
		DrawTextW(sourceDC, &text[k], 1, &rect, DT_CALCRECT);
		hBitmap = CreateCompatibleBitmap(destDC, rect.right - rect.left, rect.bottom - rect.top);
		DeleteObject(SelectObject(sourceDC, hBitmap));
		TextOutW(sourceDC, 0, 0, &text[k], 1);
		Rotate(angle + Pi/2,
			POINT{ position.x + (long)((cos(angle) + 1) * radius.x),
			position.y + (long)((sin(angle) + 1) * radius.y)},
			destDC, sourceDC, hBitmap);
		++k;
	}
	SelectObject(sourceDC, hFontPrev);
	DeleteObject(hFont);
	SelectObject(sourceDC, oldbmp);
	DeleteObject(sourceDC);
	DeleteObject(hBitmap);
	LocalFree((LOCALHANDLE)pLogFont);
}

