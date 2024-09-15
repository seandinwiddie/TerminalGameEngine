#pragma once
#include <Windows.h>

namespace InputUtils
{
	static bool IsAnyKeyPressed()
	{
		for (int i = 0; i < 256; ++i)
			if (GetAsyncKeyState(i) & 0x8000)
				return true;

		return false;
	}

	static bool IsPressingSpace() { return GetAsyncKeyState(VK_SPACE) & 0x8000; }
	static bool IsPressingA() { return GetAsyncKeyState(0x41) & 0x8000; }
	static bool IsPressingD() { return GetAsyncKeyState(0x44) & 0x8000; }
	static bool IsPressing1() { return GetAsyncKeyState(0x31) & 0x8000; }
	static bool IsPressing2() { return GetAsyncKeyState(0x32) & 0x8000; }
	static bool IsPressingEsc() { return GetAsyncKeyState(0x1B) & 0x8000; }
}