#pragma once

#include "Vector2.h"
#include "Input.h"
#include "Object.h"

class Jump
{
private:
	bool _isJump;		//ジャンプ中か?
	bool _groundJump;	//地上ジャンプ
	bool _secondJump;	//二段ジャンプが残っているか？
	bool _isAirJump;	//空中ジャンプ中か？

	bool& _hitGround;


	Vector2& _vel;
	Input*& _input;
	Object* _owner;

public:
	Jump(Input*& input, Vector2& vel, bool& hitGround, Object* owenr);
	~Jump();

	//戻り値 ジャンプ成功
	bool GroundJump();
	//戻り値 ジャンプ成功
	bool AirJump();

	void Attenuation();

	//地面に着いたときに呼ぶ
	void HitGround();

	//空中ジャンプ復活
	void RevivalAirJump();

};

