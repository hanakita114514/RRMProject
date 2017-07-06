#pragma once

#include "Vector2.h"
#include "Input.h"
#include "Object.h"

class Jump
{
private:
	bool _isJump;		//�W�����v����?
	bool _groundJump;	//�n��W�����v
	bool _secondJump;	//��i�W�����v���c���Ă��邩�H
	bool _isAirJump;	//�󒆃W�����v�����H

	bool& _hitGround;


	Vector2& _vel;
	Input*& _input;
	Object* _owner;

public:
	Jump(Input*& input, Vector2& vel, bool& hitGround, Object* owenr);
	~Jump();

	//�߂�l �W�����v����
	bool GroundJump();
	//�߂�l �W�����v����
	bool AirJump();

	void Attenuation();

	//�n�ʂɒ������Ƃ��ɌĂ�
	void HitGround();

	//�󒆃W�����v����
	void RevivalAirJump();

};

