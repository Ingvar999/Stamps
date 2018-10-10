#include "Stamp.h"
#include <math.h>

void Stamp::Rotate(float radians, POINT position, HDC destDC, HDC sourceDC, HBITMAP hBitmap)
{
	BITMAP bm;
	GetObject(hBitmap, sizeof(bm), &bm);

	float cosine = (float)cos(radians);
	float sine = (float)sin(radians);

	SetGraphicsMode(destDC, GM_ADVANCED);

	XFORM xform;
	xform.eM11 = cosine;
	xform.eM12 = sine;
	xform.eM21 = -sine;
	xform.eM22 = cosine;
	xform.eDx = position.x;
	xform.eDy = position.y;

	SetWorldTransform(destDC, &xform);

	StretchBlt(destDC, 0, 0, bm.bmWidth, bm.bmHeight, sourceDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
}
