#include "InputFactory.h"
#include "DInput.h"
#include "Keyboard.h"


InputFactory::InputFactory()
{
}


InputFactory::~InputFactory()
{
}

Input*
InputFactory::Create(const InputMode& mode, unsigned int padNum)
{
	switch (mode)
	{
	case InputMode::pad:
		return new DInput(padNum);
		break;
	case InputMode::keyboard:
		return new Keyboard();
		break;
	default:
		break;
	}

	return nullptr;
}