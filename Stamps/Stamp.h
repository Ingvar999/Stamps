#pragma once

#include <windows.h>

#define Pi 3.1416

class Stamp
{
public:
	Stamp(HDC dc, LPCWSTR str, INT f) : destDC(dc), text(str), family(f) {};
	~Stamp() {};
	virtual void Print(POINT position) = 0;

protected:
	HDC destDC;
	LPCWSTR text;
	INT family;

	void Rotate(float radians, POINT position, HDC destDC, HDC sourceDC, HBITMAP hBitmap);
};

