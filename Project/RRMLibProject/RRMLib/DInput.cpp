#include "DInput.h"
#include "WindowControl.h"
#include <stdio.h>

using namespace RRMLib;

LPDIRECTINPUT8 g_lpDI;
LPDIRECTINPUTDEVICE8A g_lpDIDevice;
DIDEVCAPS g_diDevCaps;

//インプットコールバック関数
BOOL CALLBACK 
EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	HRESULT result;
	result = g_lpDI->CreateDevice(pdidInstance->guidInstance, &g_lpDIDevice, nullptr);
	if (FAILED(result))
	{
		return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}

BOOL CALLBACK 
EnumAxesCalllback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext)
{
	HRESULT result;
	DIPROPRANGE diprg = {};

	//DirectInputの範囲設定
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = -1000;
	diprg.lMax = +1000;

	result = g_lpDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	//デッドゾーンの設定
	DIPROPDWORD diprop = {};
	diprop.diph.dwSize = sizeof(DIPROPDWORD);
	diprop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprop.diph.dwHow = DIPH_BYID;
	diprop.diph.dwObj = pdidoi->dwType;
	diprop.dwData = 2000;

	result = g_lpDIDevice->SetProperty(DIPROP_DEADZONE, &diprop.diph);

	if (FAILED(result))
	{
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}

DInput::DInput()
{

}


DInput::~DInput()
{
	if (g_lpDIDevice)
	{
		g_lpDIDevice->Release();
	}
	if (g_lpDI)
	{
		g_lpDI->Release();
	}
}

bool
DInput::Init()
{
	HRESULT result;
	HWND hwnd = WindowControl::Instance().WindowHandle();
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);

	//インプット
	result = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&g_lpDI, nullptr);

	if (FAILED(result)) {
		MessageBox(hwnd, "Can't create DirectInput object.", "Error", MB_OK);
		return false;
	}

	result = g_lpDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, nullptr,
		DIEDFL_ATTACHEDONLY);

	if (FAILED(result)) {
		MessageBox(hwnd, "Can't create DirectInput object.", "Error", MB_OK);
		return false;
	}

	if (g_lpDIDevice == nullptr)
	{
		return false;
	}

	result = g_lpDIDevice->SetDataFormat(&c_dfDIJoystick);

	if (FAILED(result)) {
		MessageBox(hwnd, "Can't create DirectInput object.", "Error", MB_OK);
		return false;
	}

	//リリース時
	//result = g_lpDIDevice->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	//デバッグモード用
	result = g_lpDIDevice->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_BACKGROUND);

	if (FAILED(result)) {
		MessageBox(hwnd, "Can't create DirectInput object.", "Error", MB_OK);
		return false;
	}

	g_diDevCaps.dwSize = sizeof(DIDEVCAPS);

	result = g_lpDIDevice->GetCapabilities(&g_diDevCaps);

	if (FAILED(result)) {
		MessageBox(hwnd, "Can't create DirectInput object.", "Error", MB_OK);
		return false;
	}

	result = g_lpDIDevice->EnumObjects(EnumAxesCalllback, (VOID*)hwnd, DIDFT_AXIS);

	if (FAILED(result)) {
		MessageBox(hwnd, "Can't create DirectInput object.", "Error", MB_OK);
		return false;
	}

	result = g_lpDIDevice->Poll();

	if (FAILED(result))
	{
		result = g_lpDIDevice->Acquire();
		while (result == DIERR_INPUTLOST)
		{
			result = g_lpDIDevice->Acquire();
		}
	}

	return true;
}

BOOL 
DInput::ReadInput()
{
	DIJOYSTATE js;
	HRESULT    hr;

	RECT rc;
	int        i;
	char       titlebar[32];
	char       subbuf[4];

	if (NULL == g_lpDIDevice) return FALSE;

	hr = g_lpDIDevice->Poll();
	if (FAILED(hr)) return FALSE;

	hr = g_lpDIDevice->GetDeviceState(sizeof(js), &js);
	if (FAILED(hr)) return FALSE;


	titlebar[0] = '\0';

	if (js.lY == -1000) strcat(titlebar, "↑");
	if (js.lY == 1000) strcat(titlebar, "↓");
	if (js.lX == -1000) strcat(titlebar, "←");
	if (js.lX == 1000) strcat(titlebar, "→");

	for (i = 0; i<32; i++) {
		if (js.rgbButtons[i] & 0x80) {
			sprintf(subbuf, ",%d", i);
			strcat(titlebar, subbuf);
		}
	}
	HWND hwnd = WindowControl::Instance().WindowHandle();

	SetWindowText(hwnd, titlebar);

	return TRUE;
}


bool 
DInput::GetJoyState(DIJOYSTATE& js)
{
	HRESULT    hr = S_OK;

	if (nullptr == g_lpDIDevice)
	{
		return false;
	}


	hr = g_lpDIDevice->Poll();

	if (FAILED(hr))
	{
		return false;
	}


	hr = g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}