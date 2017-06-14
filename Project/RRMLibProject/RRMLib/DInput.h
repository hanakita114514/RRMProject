#pragma once

#define INITGUID
//#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定

#include <dinput.h>

namespace RRMLib
{
	class DInput
	{
	private:
		DIJOYSTATE _js;

	public:
		DInput();
		~DInput();
		bool Init();
		BOOL ReadInput();

		bool GetJoyState(DIJOYSTATE& js);
	};
}