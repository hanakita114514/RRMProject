#pragma once
#include "Timer.h"

//フレームレートを計算し表示するクラス
class FPS
{
private:
	int _startTime;			//測定開始時刻
	int _count;				//カウンタ
	float _fps;
	static const int FRAME_NUM = 60;
	static const int FPs = 60;		//設定したFPS

	int _numHandle;
	int _periodHandle;
	int _fpsHandle;
	int _koronHandle;

	Position _pos;
	float _size;
	float _offset;

	Timer _time;
public:
	FPS(const Position& pos, float size);
	~FPS();

	void Update();
	void Draw();
};

