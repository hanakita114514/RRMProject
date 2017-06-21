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

	Timer _time;
public:
	FPS();
	~FPS();

	void Update();
	void Draw();
};

