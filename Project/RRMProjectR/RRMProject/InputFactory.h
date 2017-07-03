#pragma once

#include "Input.h"

class InputFactory
{
public:
	InputFactory();
	~InputFactory();

	//mode 入力モード
	//padNum プレイヤーナンバー
	static Input* Create(const InputMode& mode, unsigned int padNum);
};

