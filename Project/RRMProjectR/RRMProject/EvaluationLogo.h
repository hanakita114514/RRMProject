#pragma once


#include <map>
#include "Vector2.h"

class EvaluationLogo
{
private:
	enum class State
	{
		start,
		end,
	};
private:
	State _state;

	typedef void(EvaluationLogo::*_func)(int _handle, const Position& pos);

	float _width;
	float _height;

	std::map<State, _func> _draw;
	void StartDraw(int handle, const Position& pos);
	void EndDraw(int handle, const Position& pos);

public:
	EvaluationLogo();
	~EvaluationLogo();

	void Draw(int handle, const Position& pos);

	bool IsEnd() { return _state == State::end; }
};

