#pragma once

class HitStop
{
private:
	float _stopTime;


public:
	HitStop();
	~HitStop();

	void Update();

	//�q�b�g�X�g�b�v������
	void HitStopTime(float stopTime);

	//�q�b�g�X�g�b�v�����H
	bool IsHitStop();
};

