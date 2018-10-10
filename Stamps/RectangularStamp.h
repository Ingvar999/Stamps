#pragma once
#include "Stamp.h"

class RectangularStamp : public Stamp
{
public:
	RectangularStamp(HDC dc, LPCWSTR str, INT f, POINT s) :
		Stamp(dc, str, f), sides(s) {};
	~RectangularStamp() {};
	void Print(POINT position) override;
protected:
	POINT sides;
};

