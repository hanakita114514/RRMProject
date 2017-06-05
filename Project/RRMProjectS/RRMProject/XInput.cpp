#include "XInput.h"


XInput::XInput(int inputType)
{
	int padNumber[4] =
	{
		DX_INPUT_PAD1,
		DX_INPUT_PAD2,
		DX_INPUT_PAD3,
		DX_INPUT_PAD4,
	};

	_inputType = padNumber[inputType];

	//ƒL[—š—ğ‚Ì‰Šú‰»
	for (int i = 0; i < HISTORY_NUM; i++)
	{
		XINPUT_STATE x = {};
		//_history[i] = x;
	}
}


XInput::~XInput()
{
}

void
XInput::Update()
{
	//—š—ğ‚ğ‚Æ‚Á‚Ä‚¢‚­
	for (int i = HISTORY_NUM - 1; i > 0; i--)
	{
		_history[i] = _history[i - 1];
	}

	_history[0] = _xinput;
	DxLib::GetJoypadXInputState(_inputType, &_xinput);
}

bool
XInput::IsTriger(int keyType)
{
	if (~_xinput.Buttons[keyType] & _history[0].Buttons[keyType])
	{
		return true;
	}
	return false;
}

bool
XInput::IsPress(int keyType)
{
	if (_xinput.Buttons[keyType])
	{
		return true;
	}
	return false;
}

bool
XInput::IsRelease(int keyType)
{
	return false;
}

bool
XInput::IsRepeat(int keyType)
{
	return false;
}