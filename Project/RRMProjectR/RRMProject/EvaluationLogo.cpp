#include "EvaluationLogo.h"
#include <RRMLib.h>

static const float WIDTH = 64.f;
static const float HEIGHT = 64.f;

static const float SPEED = 10.f;


EvaluationLogo::EvaluationLogo()
{
	_height = HEIGHT * 4;
	_width = WIDTH * 4;

	_state = State::start;
	_draw[State::start] = &EvaluationLogo::StartDraw;
	_draw[State::end] = &EvaluationLogo::EndDraw;
}


EvaluationLogo::~EvaluationLogo()
{
}

void 
EvaluationLogo::StartDraw(int handle, const Position& pos)
{
	_width -= SPEED;
	_height -= SPEED;

	RRMLib::DrawExtendGraph(pos.x - _width / 2, pos.y - _height / 2,
		pos.x + _width / 2, pos.y + _height / 2, handle, true, false);

	if (_width <= WIDTH && _height <= HEIGHT)
	{
		_width = WIDTH;
		_height = HEIGHT;
		_state = State::end;

	}
}

void 
EvaluationLogo::EndDraw(int handle, const Position& pos)
{
	RRMLib::DrawExtendGraph(pos.x - _width / 2, pos.y - _height / 2,
		pos.x + _width / 2, pos.y + _height / 2, handle, true, false);
}

void
EvaluationLogo::Draw(int handle, const Position& pos)
{
	(this->*_draw[_state])(handle, pos);
}