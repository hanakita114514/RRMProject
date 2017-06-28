#pragma once
#include <dinput.h>

namespace RRMLib
{
	class Keyboard
	{
	private:
		//DirectInput�I�u�W�F�N�g�|�C���^
		LPDIRECTINPUT8 _dinput;
		//DirectInput�f�o�C�X��I�u�W�F�N�g�|�C���^
		LPDIRECTINPUTDEVICE8 _keyDevice;
	public:
		Keyboard();
		~Keyboard();

		//������
		bool Init();
		//char[256]�̃o�b�t�@��n��
		bool GetKeyState(char* keyBuf);
	};
}
