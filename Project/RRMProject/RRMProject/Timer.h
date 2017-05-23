#pragma once

#include <chrono>

struct Time
{
	long long int mimutes;
	long long int seconds;
	long long int millisec;

};

class Timer
{
private:
	std::chrono::system_clock::time_point _start;

public:
	Timer();
	~Timer();

	void Start();				//計測開始

	void Stop();				//計測を停止する

	void Reset();				//タイマーをリセットする

	Time  GetTimes();			//計測時間を取得する(各単位)

	Time GetTime();				//計測時間(分、秒、ミリ秒分け)

	void Draw();				//計測時間を表示
};

