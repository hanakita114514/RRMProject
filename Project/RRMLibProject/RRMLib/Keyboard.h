#pragma once
#include <dinput.h>

namespace RRMLib
{
	class Keyboard
	{
	private:
		//DirectInputオブジェクトポインタ
		LPDIRECTINPUT8 _dinput;
		//DirectInputデバイス･オブジェクトポインタ
		LPDIRECTINPUTDEVICE8 _keyDevice;
	public:
		Keyboard();
		~Keyboard();

		//初期化
		bool Init();
		//char[256]のバッファを渡す
		bool GetKeyState(char* keyBuf);
	};
}
