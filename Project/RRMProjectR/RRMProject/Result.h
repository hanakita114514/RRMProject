#pragma once

#include <map>
#include "EndCall.h"
#include "Score.h"
#include "Combo.h"

class Logo;

class Result
{
private:
	enum class State
	{
		start,
		middle,
		end,
	};
private:
	int _handle;

	typedef void (Result::*_func)();
	std::map<State, _func> _update;

	void StartUpdate();
	void MiddleUpdate();
	void EndUpdate();

	State _state;

	EndCall _endCall;

	Logo* _logo;

	Score& _score;
	int _maxCombo;


public:
	Result(Score& score);
	~Result();

	void Update();

	bool IsEnd();
};

