#pragma once

#include "Input.h"

class InputFactory
{
public:
	InputFactory();
	~InputFactory();

	//mode ���̓��[�h
	//padNum �v���C���[�i���o�[
	static Input* Create(const InputMode& mode, unsigned int padNum);
};

