#pragma once

#include "Object.h"

//���E���͓���̓G���X���[���[�V�����ɂ�����
class SlowDown
{
private:
	int _slowTime;	//�x�������鎞��
	int _time;

	bool _isSlow;	//�X���[���[�V�����������Ԃ��H
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
