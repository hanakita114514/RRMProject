#pragma once

#include <map>
#include "EndCall.h"

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

public:
	Result();
	~Result();

	void Update();

	bool IsEnd();
};

