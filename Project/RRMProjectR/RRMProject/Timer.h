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

	void Start();				//�v���J�n

	void Stop();				//�v�����~����

	void Reset();				//�^�C�}�[�����Z�b�g����

	Times  GetTimes();			//�v�����Ԃ��擾����(�e�P��)

	Times GetTime();				//�v������(���A�b�A�~���b����)

	void Draw();				//�v�����Ԃ�\��
};

