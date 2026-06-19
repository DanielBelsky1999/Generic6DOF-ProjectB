#pragma once

#include <windows.h>

void GetSurfaceCommands(double* s) {

	double* d1 = &s[0];
	double* d2 = &s[1];
	double* d3 = &s[2];
	double* d4 = &s[3];

	bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
	bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
	bool left = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
	bool right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;

	bool less = (GetAsyncKeyState(VK_OEM_COMMA) & 0x8000) != 0;
	bool greater = (GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) != 0;

	double effective_yaw = (static_cast<double>(greater) - static_cast<double>(less));
	double effective_pitch = (static_cast<double>(up) - static_cast<double>(down));
	double effective_roll = (static_cast<double>(right) - static_cast<double>(left));

	*d1 = (effective_roll + effective_pitch - effective_yaw) / 3.0;
	*d2 = (effective_roll + effective_pitch + effective_yaw) / 3.0;
	*d3 = (effective_roll - effective_pitch + effective_yaw) / 3.0;
	*d4 = (effective_roll - effective_pitch - effective_yaw) / 3.0;
}

