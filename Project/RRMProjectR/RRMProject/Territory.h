#pragma once
#include "Rect.h"
#include "Vector2.h"


//Terrytory�N���X
//�G�̈ړ��͈͂Ƃ���ݒ肷��N���X
class Territory
{
private:
	Rect _range;			//�̈�͈̔�
	bool _outRange;			//�̈�O�ɏo�����ǂ���
public:
	Territory();
	~Territory();

	void Update(const Rect& rc);

	void Set(float xRange, float yRange, Vector2 pos);

	//�̈�͈̔͊O�ɏo�����H
	bool IsOutRange() { return _outRange; }

	//�ړ������𔽓]�����Ƃ��Ɏg���Ă�������
	void InRange() { _outRange = false; }
};

