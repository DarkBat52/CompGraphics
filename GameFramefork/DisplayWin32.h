#pragma once

#include <Windows.h>

class DisplayWin32
{
public:

	long ClientHeight = 800;
	long ClientWidth = 1200;

	WNDCLASSEX wc;
	HINSTANCE hInstance;
	HWND hWnd;
	// Module;
	
	DisplayWin32(WNDPROC WndProc);
	// DisplayWin32(long height, long width);

private:

	LPCWSTR applicationName = L"Le Square";
};

