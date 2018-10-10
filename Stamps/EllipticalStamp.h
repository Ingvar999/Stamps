#pragma once
#include "Stamp.h"

class EllipticalStamp : public Stamp
{
public:
	EllipticalStamp(HDC dc, LPCWSTR str, INT f, POINT rad) :
		Stamp(dc, str, f), radius(rad) {};
	~EllipticalStamp() {};
	void Print(POINT position) override;
protected:
	POINT radius;
};

