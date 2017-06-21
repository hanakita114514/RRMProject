#pragma once
#include "Timer.h"

//�t���[�����[�g���v�Z���\������N���X
class FPS
{
private:
	int _startTime;			//����J�n����
	int _count;				//�J�E���^
	float _fps;
	static const int FRAME_NUM = 60;
	static const int FPs = 60;		//�ݒ肵��FPS

	Timer _time;
public:
	FPS();
	~FPS();

	void Update();
	void Draw();
};

