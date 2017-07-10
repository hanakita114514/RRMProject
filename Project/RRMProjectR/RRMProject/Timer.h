#pragma once

#include <chrono>
#include "Vector2.h"

struct Times
{
	long long int mimutes;
	long long int seconds;
	long long int millisec;

};

class Timer
{
private:
	std::chrono::system_clock::time_point _start;

	Times _endTime;
	bool _isEnd;

	int _timeHandle;
	int _handle;
	int _koronHandle;

	Position _pos;
	float _size;
	float _offset;

public:
	Timer();
	Timer(const Position& pos, float size);
	~Timer();

	void Start();				//計測開始

	void Stop();				//計測を停止する

	void Reset();				//タイマーをリセットする

	Times  GetTimes();			//計測時間を取得する(各単位)

	Times GetTime();				//計測時間(分、秒、ミリ秒分け)

	void Draw();				//計測時間を表示
};

