#pragma once

#include <map>
#include "EndCall.h"

class Result
{
private:
	enum class State
	{
		start,
		end,
	};
private:
	int _handle;

	typedef void (Result::*_func)();
	std::map<State, _func> _update;

	void StartUpdate();
	void EndUpdate();

	State _state;

	EndCall _endCall;

public:
	Result();
	~Result();

	void Update();
};

