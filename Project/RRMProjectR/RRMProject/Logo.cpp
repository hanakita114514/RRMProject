#include "Logo.h"
#include <RRMLib.h>
#include "common.h"

static const float LOGO_H = 96.0f;
static const float LOGO_W = 256.0f;

static const float INIT_H = 10.0f;

static const float SPEED = 100.0f;

Logo::Logo(int handle , const Position& pos)
	: _handle(handle), _pos(pos)
{
	_update[State::start] = &Logo::StartUpdate;
	_update[State::middle] = &Logo::MiddleUpdate;
	_update[State::end] = &Logo::EndUpdate;
	_state = State::start;

	_height = 0;
	_width = 0;
	
	_middleFlag = 0;
}

Logo::~Logo()
{
}

void 
Logo::StartUpdate()
{
	_width += SPEED;
	RRMLib::DrawExtendGraph((_pos.x) - (_width / 2), (_pos.y) - (INIT_H / 2),
		(_pos.x) + (_width / 2), (_pos.y) + (INIT_H / 2), _handle, true, false);

	if (_width >= WINDOW_WIDTH)
	{
		_width = WINDOW_WIDTH;
		_state = State::middle;
	}
}

void 
Logo::MiddleUpdate()
{
	_height += SPEED;
	_width -= SPEED;

	RRMLib::DrawExtendGraph((_pos.x) - (_width / 2), (_pos.y) - (_height / 2),
		(_pos.x) + (_width / 2), (_pos.y) + (_height / 2), _handle, true, false);

	if (_height >= LOGO_H)
	{
		_height = LOGO_H;
		_middleFlag |= 1;
	}
	if (_width <= LOGO_W)
	{
		_width = LOGO_W;
		_middleFlag |= 2;
	}

	if ((_middleFlag & 3) == 3)
	{
		_state = State::end;
	}
}

void 
Logo::EndUpdate()
{
	RRMLib::DrawExtendGraph((_pos.x) - (_width / 2), (_pos.y) - (_height / 2),
		(_pos.x) + (_width / 2), (_pos.y) + (_height / 2), _handle, true, false);
}

void
Logo::Update()
{
	(this->*_update[_state])();
}