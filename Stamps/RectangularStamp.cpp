#include "RectangularStamp.h"

#include <math.h>
#include <strsafe.h>

void RectangularStamp::Print(POINT position)
{
	size_t textLength = wcslen(text);
	INT frameWidth = 0;
	for (int i = 0; i < 10; ++i)
		frameWidth = (INT)ceil((double)(sides.x + sides.y - 8*frameWidth) * 2 / textLength);
	INT charHeight = frameWidth << 1;
	RECT rect;
	POINT pos = position;
	pos.x += charHeight;

	INT k = 0;
	FLOAT angle = 0;
	INT lettersPerWidth = (INT)ceil((double)(sides.x - 2*charHeight)/ frameWidth);
	INT lettersPerHeight = (INT)ceil((double)(sides.y - 2 * charHeight) / frameWidth);
	INT printedLetters = lettersPerWidth;

	HDC sourceDC = CreateCompatibleDC(destDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(destDC, 0, 0);
	HBITMAP oldbmp = (HBITMAP)SelectObject(sourceDC, hBitmap);

	PLOGFONT pLogFont = (PLOGFONT)LocalAlloc(LPTR, sizeof(LOGFONT));
	pLogFont->lfPitchAndFamily = family;
	//StringCchCopy(pLogFont->lfFaceName, wcslen(font), (STRSAFE_LPSTR)font);
	pLogFont->lfWeight = FW_NORMAL;
	pLogFont->lfHeight = charHeight;
	pLogFont->lfWidth = (INT)ceil((double)(frameWidth * 2) / 3);;
	HFONT hFont = CreateFontIndirect(pLogFont);
	HGDIOBJ hFontPrev = SelectObject(sourceDC, hFont);

	for (int i = 1; i <= 4; ++i) {
		while (k < printedLetters && text[k])
		{
			DrawTextW(sourceDC, &text[k], 1, &rect, DT_CALCRECT);
			hBitmap = CreateCompatibleBitmap(destDC, rect.right - rect.left, rect.bottom - rect.top);
			DeleteObject(SelectObject(sourceDC, hBitmap));
			TextOutW(sourceDC, 0, 0, &text[k], 1);
			Rotate(angle, pos, destDC, sourceDC, hBitmap);
			switch (i) {
			case 1:
				pos.x += frameWidth;
				break;
			case 2:
				pos.y += frameWidth;
				break;
			case 3:
				pos.x -= frameWidth;
				break;
			case 4:
				pos.y -= frameWidth;
				break;
			}
			++k;
		}
		angle += Pi / 2;
		switch (i) {
		case 1:
			pos.x = position.x + sides.x;
			pos.y += charHeight;
			printedLetters += lettersPerHeight;
			break;
		case 2:
			pos.y = position.y + sides.y;
			pos.x -= charHeight;
			printedLetters += lettersPerWidth;
			break;
		case 3:
			pos.x = position.x;
			pos.y -= charHeight;
			printedLetters += lettersPerHeight;
			break;
		}
	}
	SelectObject(sourceDC, hFontPrev);
	DeleteObject(hFont);
	SelectObject(sourceDC, oldbmp);
	DeleteObject(sourceDC);
	DeleteObject(hBitmap);
	LocalFree((LOCALHANDLE)pLogFont);
}
