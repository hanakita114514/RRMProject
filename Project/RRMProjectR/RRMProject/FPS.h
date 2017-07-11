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

