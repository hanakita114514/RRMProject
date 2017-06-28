#include "Keyboard.h"
#include "WindowControl.h"


using namespace RRMLib;

Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
	if (_keyDevice)
	{
		_keyDevice->Unacquire();
		_keyDevice->Release();
		_keyDevice = nullptr;
	}
	if (_dinput)
	{
		_dinput->Release();
		_dinput = nullptr;
	}
}

bool 
Keyboard::Init()
{
	HRESULT hr;
	HWND hwnd = WindowControl::Instance().WindowHandle();

	//DirectInputオブジェクトを作成
	hr = DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&_dinput,
		nullptr);

	if (FAILED(hr))
	{
		MessageBox(nullptr, "Can't Create DirectInput", "Error", MB_OK);
		return false;
	}

	//DirectInputデバイスオブジェクトを作成
	hr = _dinput->CreateDevice(
		GUID_SysKeyboard,
		&_keyDevice,
		nullptr
	);

	//デバイスをキーボードに設定
	hr = _keyDevice->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(hr))
	{
		MessageBox(nullptr, "Can't Create DirectInput", "Error", MB_OK);
		return false;
	}

	//強調レベルの設定

	//常時取得
	hr = _keyDevice->SetCooperativeLevel(
		hwnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND
	);

	if (FAILED(hr))
	{
		MessageBox(nullptr, "Can't Create DirectInput", "Error", MB_OK);
		return false;
	}

	_keyDevice->Poll();

	//アクセス権取得
	if (FAILED(hr))
	{
		hr = _keyDevice->Acquire();
		while (hr == DIERR_INPUTLOST)
		{
			hr = _keyDevice->Acquire();
		}
	}
}

bool 
Keyboard::GetKeyState(char* keyBuf)
{
	HRESULT hr;
	if (_keyDevice == nullptr)
	{
		return false;
	}

	hr = _keyDevice->Acquire();

	_keyDevice->Poll();

	char key[256];
	_keyDevice->GetDeviceState(sizeof(key),	&key);

	int size = sizeof(key);

	for (int i = 0; i <size ; i++)
	{
		keyBuf[i] = key[i] & 0x80;
	}
}