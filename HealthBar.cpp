#include "stdafx.h"

HealthBar::HealthBar() :MyObject(healthbar1, 0, 500) {}


HealthBar::~HealthBar(){
}

void HealthBar::Select(HDC &mdc, HDC &bufdc, float rate){
	if (show) {
		SelectObject(bufdc, image);
		BitBlt(mdc, x, y, width*rate, height, bufdc, 0, 46, SRCAND);
		BitBlt(mdc, x, y, width*rate, height, bufdc, 0, 0, SRCPAINT);
	}
}