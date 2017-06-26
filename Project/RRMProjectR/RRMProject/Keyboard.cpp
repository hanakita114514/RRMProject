#include "Keyboard.h"
#include <RRMLib.h>

Keyboard::Keyboard()
{
	for (int i = 0; i < keyNum; i++)
	{
		_key[i] = 0;
		_keyHistory[i] = 0;
	}

	//�L�[��ۑ�
	_keyType[InputType::keyA] = KEY_Z;
	_keyType[InputType::keyB] = KEY_X;
	_keyType[InputType::keyX] = KEY_C;
	_keyType[InputType::keyY] = KEY_V;
	_keyType[InputType::keyL] = KEY_A;
	_keyType[InputType::keyR] = KEY_S;
	_keyType[InputType::keyStart] = KEY_RETURN;
	_keyType[InputType::keyBack] = KEY_ESCAPE;
}


Keyboard::~Keyboard()
{
}

void
Keyboard::Update()
{
	for (int i = 0; i < keyNum; i++)
	{
		_keyHistory[i] = _key[i];
	}

	RRMLib::GetKeyboardState(_key);
}

//�{�^�����������Ƃ�
bool
Keyboard::IsTriger(const InputType& inputType)
{
	if (_keyHistory[_keyType[inputType]] & _keyHistory[_keyType[inputType]])
	{
		return true;
	}
	return false;
}

//�{�^���������Ă����
bool
Keyboard::IsPress(const InputType& inputType)
{
	if (_key[_keyType[inputType]])
	{
		return true;
	}
	return false;
}

//�{�^���𗣂����Ƃ�
bool
Keyboard::IsRelease(const InputType& inputType)
{
	if (~_key[_keyType[inputType]] & _keyHistory[_keyType[inputType]])
	{
		return true;
	}
	return false;
}

//�{�^���̃��s�[�g
bool 
Keyboard::IsRepeat(const InputType& inputType)
{
	return false;
}

void 
Keyboard::KeySwap(const InputType& key1, const InputType& key2)
{
	int tmp = _keyType[key1];
	_keyType[key1] = _keyType[key2];
	_keyType[key2] = tmp;
}