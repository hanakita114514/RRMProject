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

	void Start();				//�v���J�n

	void Stop();				//�v�����~����

	void Reset();				//�^�C�}�[�����Z�b�g����

	Time  GetTimes();			//�v�����Ԃ��擾����(�e�P��)

	Time GetTime();				//�v������(���A�b�A�~���b����)

	void Draw();				//�v�����Ԃ�\��
};

