#include "FPS.h"
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

FPS::FPS(const Position& pos, float size) : _startTime(0), _count(0), _fps(0)
{
	_numHandle = RRMLib::LoadGraph("Resource/img/UI/Number/Number.png");
	_periodHandle = RRMLib::LoadGraph("Resource/img/UI/period.png");
	_fpsHandle = RRMLib::LoadGraph("Resource/img/UI/FPS.png");
	_koronHandle = RRMLib::LoadGraph("Resource/img/UI/koron2.png");

	_pos = pos;
	_size = size;
	_offset = _size * 0.5;
}


FPS::~FPS()
{
}


void 
FPS::Update()
{
	if (_count == 0)
	{
		_time.Start();
		_startTime = _time.GetTimes().millisec;
	}
	if (_count == FRAME_NUM)
	{
		int t = _time.GetTimes().millisec;
		_fps = 1000.0f / ((t - _startTime) / (float)FRAME_NUM);
		_count = 0;
		_startTime = t;
	}
	++_count;
}

void 
FPS::Draw()
{
	//char titleBar[32];
	//titleBar[0] = '\0';
	//sprintf(titleBar, "%.1f", _fps);

	//RRMLib::SetMainWindowText(titleBar);

	float periodOffsetY = _size * 0.15f;
	unsigned int idx = 0;
	float i = 0;
	Vector2 uv;


	//FPS文字描画
	RRMLib::DrawExtendGraph((_pos.x - _size) + i * _offset - 5, _pos.y - _size / 2,
		(_pos.x + _size) + i * _offset - 5, _pos.y + _size / 2, _fpsHandle);

	i += 1.5f;
	RRMLib::DrawExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2, _koronHandle);

	//十の位
	i += 2.0f;
	uv = UV[(int)(_fps / NUM) % NUM];
	RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _numHandle, true, false);

	//一の位
	++i;
	uv = UV[(int)(_fps) % NUM];
	RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _numHandle, true, false);

	//ピリオド
	i += 0.5f;
	RRMLib::DrawExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2 + periodOffsetY,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2 + periodOffsetY, _periodHandle);

	//小数点第一位
	i += 0.8f;
	uv = UV[(int)(_fps * NUM) % NUM];
	RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) + i * _offset, _pos.y - _size / 2,
		(_pos.x + _size / 2) + i * _offset, _pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _numHandle, true, false);
}