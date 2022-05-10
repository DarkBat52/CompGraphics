#include "InputDevice.h"

#include "Game.h"
#include <windowsx.h>
//#include <iostream>

bool InputDevice::IsKeyDown(uint64_t Key)
{
	return PressedKeys.find(Key) != PressedKeys.end();
}

void InputDevice::PreInputProcess()
{
	MouseMoveDeltaX = 0.0f;
	MouseMoveDeltaY = 0.0f;
}

void InputDevice::GetMouseDelta(float& OutX, float& OutY)
{
	OutX = MouseMoveDeltaX;
	OutY = MouseMoveDeltaY;
}

LRESULT InputDevice::HandleMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_KEYDOWN:

		if (wparam == 27)
		{
			Game::Get()->Exit();
			return 0;
		}

		PressedKeys.insert(wparam);

		return 0;
	case WM_KEYUP:
		PressedKeys.erase(wparam);
		return 0;
	case WM_MOUSEMOVE:
	{	
		const int posX = GET_X_LPARAM(lparam);
		const int posY = GET_Y_LPARAM(lparam);
		if (!(wparam & MK_SHIFT)) {
			DisplayWin32* disp = Game::Get()->Display;
			MouseMoveDeltaX = (PrevPosX - posX) / static_cast<float>(disp->ClientWidth);
			MouseMoveDeltaY = (PrevPosY - posY) / static_cast<float>(disp->ClientHeight);
		}
		PrevPosX = posX;
		PrevPosY = posY;
		break;
	}
	default:
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
}
