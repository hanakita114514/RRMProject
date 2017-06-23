#include "Timer.h"
#include <stdio.h>


Timer::Timer()
{
}


Timer::~Timer()
{
}


void 
Timer::Start()
{
	_start = std::chrono::system_clock::now();
}

void 
Timer::Stop()
{
	
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
	ret.mimutes = std::chrono::duration_cast<std::chrono::minutes>(dur).count();
	ret.seconds = std::chrono::duration_cast<std::chrono::seconds>(dur).count() % 60;
	ret.millisec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() % 1000;

	return ret;
}
void 
Timer::Draw()
{

}