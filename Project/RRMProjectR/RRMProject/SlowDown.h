#pragma once

#include "Object.h"

//世界又は特定の敵をスローモーションにさせる
class SlowDown
{
private:
	int _slowTime;	//遅くさせる時間
	int _time;

	bool _isSlow;	//スローモーションさせる状態か？
	float _resio;

public:
	SlowDown();
	~SlowDown();

	void Update();

	void SlowMotion(int time);
	void SlowMotion(int time, Object* other);

	void TheWorld(int time);
	void TheWorld(int time, Object* other);

};

