#pragma once

#define INITGUID
//#define DIRECTINPUT_VERSION     0x0800          // DirectInput�̃o�[�W�����w��

#include <dinput.h>

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

