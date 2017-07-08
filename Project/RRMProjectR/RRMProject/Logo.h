#pragma once

#include <map>
#include "Vector2.h"

class Logo
{
private:
	enum class State : unsigned int
	{
		start,
		middle,
		end,
	};

private:
	int _handle;

	typedef void (Logo::*_func)();

	State _state;
	std::map<State, _func> _update;
	void StartUpdate();
	void MiddleUpdate();
	void EndUpdate();
	
	float _width;
	float _height;

	short _middleFlag;

	Vector2 _pos;

public:
	//pos íÜâõç¿ïW
	Logo(int handle, const Position& pos);
	~Logo();

	void Update();

	bool IsEnd() { return _state == State::end; }
};

