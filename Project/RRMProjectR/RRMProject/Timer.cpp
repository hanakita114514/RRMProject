#include "Timer.h"
#include <stdio.h>
#include <RRMLib.h>

static const float NUMBER_W = 84.4f;
static const float NUMBER_H = 88.5f;
static const float OFFSET = 32.0f;

static const int NUM = 10;
static const Vector2 UV[NUM]
{
	Vector2(NUMBER_W * 0, NUMBER_H * 0),
	Vector2(NUMBER_W * 1, NUMBER_H * 0),
	Vector2(NUMBER_W * 2, NUMBER_H * 0),
	Vector2(NUMBER_W * 3, NUMBER_H * 0),
	Vector2(NUMBER_W * 4, NUMBER_H * 0),
	Vector2(NUMBER_W * 0, NUMBER_H * 1),
	Vector2(NUMBER_W * 1, NUMBER_H * 1),
	Vector2(NUMBER_W * 2, NUMBER_H * 1),
	Vector2(NUMBER_W * 3, NUMBER_H * 1),
	Vector2(NUMBER_W * 4, NUMBER_H * 1),
};

Timer::Timer()
{
	_handle = RRMLib::LoadGraph("Resource/img/UI/Number/Number.png");
	_koronHandle = RRMLib::LoadGraph("Resource/img/UI/Number/koron.png");
	_timeHandle = RRMLib::LoadGraph("Resource/img/UI/time.png");

	_pos = Position(0,0);
	_size = 0;
	_offset = _size / 2;
	_isEnd = false;
}

Timer::Timer(const Position& pos, float size)
{
	_handle = RRMLib::LoadGraph("Resource/img/UI/Number/Number.png");
	_koronHandle = RRMLib::LoadGraph("Resource/img/UI/Number/koron.png");
	_timeHandle = RRMLib::LoadGraph("Resource/img/UI/Logo/time.png");

	_pos = pos;
	_size = size;
	_offset = _size / 2;
	_isEnd = false;
}


Timer::~Timer()
{
}


void 
Timer::Start()
{
	_start = std::chrono::system_clock::now();
	_isEnd = false;
}

void 
Timer::Stop()
{
	_isEnd = true;
	_endTime = GetTime();
}

void 
Timer::Reset()
{
	Start();
}

Times
Timer::GetTimes()
{
	Times ret = {};
	auto end = std::chrono::system_clock::now();
	auto dur = end - _start;
	ret.mimutes = std::chrono::duration_cast<std::chrono::minutes>(dur).count();
	ret.seconds = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
	ret.millisec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	return ret;
}

Times
Timer::GetTime()
{
	Times ret = {};

	auto end = std::chrono::system_clock::now();
	auto dur = end - _start;
	ret.mimutes = std::chrono::duration_cast<std::chrono::minutes>(dur).count() % 60;
	ret.seconds = std::chrono::duration_cast<std::chrono::seconds>(dur).count() % 60;
	ret.millisec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() % 1000;

	return ret;
}
void 
Timer::Draw()
{
	Vector2 uv;
	Times times;
	if (_isEnd)
	{
		times = _endTime;
	}
	else
	{
		times = GetTime();
	}
	unsigned int idx;
	float i = 0;

	//Time•¶Žš•`‰æ
	RRMLib::DrawExtendGraph((_pos.x - _size) + i * _offset - 5, _pos.y - _size / 2 - 3,
		(_pos.x + _size) + i * _offset - 5, _pos.y + _size / 2 - 3, _timeHandle);

	i+= 1.5f;
	RRMLib::DrawExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2, _koronHandle);

	//•ª•`‰æ
	i += 5;
	uv = UV[(times.mimutes / 10) % 10];
	RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

	++i;
	uv = UV[(times.mimutes) % 10];
	RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

	++i;
	RRMLib::DrawExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2, _koronHandle);

	++i;
	//•b•`‰æ
	uv = UV[(times.seconds / 10) % 10];
	RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

	++i;
	uv = UV[(times.seconds) % 10];
	RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

	++i;
	RRMLib::DrawExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2, _koronHandle);

	//ƒ~ƒŠ•b•`‰æ
	++i;
	uv = UV[(times.millisec / 100) % 10];
	RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

	++i;
	uv = UV[(times.millisec / 10) % 10];
	RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

}

void 
Timer::Draw(const Position& pos, float size)
{
	Vector2 uv;
	Times times;
	if (_isEnd)
	{
		times = _endTime;
	}
	else
	{
		times = GetTime();
	}
	unsigned int idx;
	float i = 0;

	float offset = size * 0.5;

	////Time•¶Žš•`‰æ
	//RRMLib::DrawExtendGraph((pos.x - size) + i * offset - 5, pos.y - size / 2 - 3,
	//	(pos.x + size) + i * offset - 5, pos.y + size / 2 - 3, _timeHandle);

	//i += 1.5f;
	//RRMLib::DrawExtendGraph((pos.x - size / 2) + i * offset, pos.y - size / 2,
	//	(pos.x + size / 2) + i * offset, pos.y + size / 2, _koronHandle);

	//•ª•`‰æ
	//i += 5;
	uv = UV[(times.mimutes / 10) % 10];
	RRMLib::DrawRectExtendGraph((pos.x - size / 2) + i * offset, pos.y - size / 2,
		(pos.x + size / 2) + i * offset, pos.y + size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

	++i;
	uv = UV[(times.mimutes) % 10];
	RRMLib::DrawRectExtendGraph((pos.x - size / 2) + i * offset, pos.y - size / 2,
		(pos.x + size / 2) + i * offset, pos.y + size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

	++i;
	RRMLib::DrawExtendGraph((pos.x - size / 2) + i * offset, pos.y - size / 2,
		(pos.x + size / 2) + i * offset, pos.y + size / 2, _koronHandle);

	++i;
	//•b•`‰æ
	uv = UV[(times.seconds / 10) % 10];
	RRMLib::DrawRectExtendGraph((pos.x - size / 2) + i * offset, pos.y - size / 2,
		(pos.x + size / 2) + i * offset, pos.y + size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

	++i;
	uv = UV[(times.seconds) % 10];
	RRMLib::DrawRectExtendGraph((pos.x - size / 2) + i * offset, pos.y - size / 2,
		(pos.x + size / 2) + i * offset, pos.y + size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

	++i;
	RRMLib::DrawExtendGraph((pos.x - size / 2) + i * offset, pos.y - size / 2,
		(pos.x + size / 2) + i * offset, pos.y + size / 2, _koronHandle);

	//ƒ~ƒŠ•b•`‰æ
	++i;
	uv = UV[(times.millisec / 100) % 10];
	RRMLib::DrawRectExtendGraph((pos.x - size / 2) + i * offset, pos.y - size / 2,
		(pos.x + size / 2) + i * offset, pos.y + size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

	++i;
	uv = UV[(times.millisec / 10) % 10];
	RRMLib::DrawRectExtendGraph((pos.x - size / 2) + i * offset, pos.y - size / 2,
		(pos.x + size / 2) + i * offset, pos.y + size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);
}