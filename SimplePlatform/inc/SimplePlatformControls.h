#pragma once
#include "TControls.h"

struct SimplePlatformControls : TControls {
	bool ignition = false;
	double fins[4] = { 0.0,0.0,0.0,0.0 };
};
