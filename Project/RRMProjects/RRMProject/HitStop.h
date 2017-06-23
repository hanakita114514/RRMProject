#pragma once

class HitStop
{
private:
	float _stopTime;


public:
	HitStop();
	~HitStop();

	void Update();

	//ヒットストップさせる
	void HitStopTime(float stopTime);

	//ヒットストップ中か？
	bool IsHitStop();
};

