#pragma once
#include <Windows.h>

namespace InputUtils
{
	inline bool IsAnyKeyPressed()
	{
		for (int i = 0; i < 256; ++i)
			if (GetAsyncKeyState(i) & 0x8000)
				return true;

		return false;
	}
	inline bool IsPressingSpace() { return GetAsyncKeyState(VK_SPACE) & 0x8000; }
	
	inline bool IsPressingW() { return GetAsyncKeyState(0x57) & 0x8000; }
	inline bool IsPressingA() { return GetAsyncKeyState(0x41) & 0x8000; }
	inline bool IsPressingS() { return GetAsyncKeyState(0x53) & 0x8000; }
	inline bool IsPressingD() { return GetAsyncKeyState(0x44) & 0x8000; }

	inline bool IsPressingArrowUp() { return GetAsyncKeyState(VK_UP) & 0x8000; }
	inline bool IsPressingArrowDown() { return GetAsyncKeyState(VK_DOWN) & 0x8000; }
	inline bool IsPressingArrowLeft() { return GetAsyncKeyState(VK_LEFT) & 0x8000; }
	inline bool IsPressingArrowRight() { return GetAsyncKeyState(VK_RIGHT) & 0x8000; }

	inline bool IsPressing1() { return GetAsyncKeyState(0x31) & 0x8000; }
	inline bool IsPressing2() { return GetAsyncKeyState(0x32) & 0x8000; }
	inline bool IsPressing3() { return GetAsyncKeyState(0x33) & 0x8000; }
	inline bool IsPressing4() { return GetAsyncKeyState(0x34) & 0x8000; }
	inline bool IsPressing0() { return GetAsyncKeyState(0x30) & 0x8000; }
	inline bool IsPressing9() { return GetAsyncKeyState(0x39) & 0x8000; }
	inline bool IsPressingEsc() { return GetAsyncKeyState(0x1B) & 0x8000; }
}