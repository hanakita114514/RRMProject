#pragma once
#include "Food.h"
#include <map>

class GeneralFood : public Food
{
private:
	enum class State : unsigned int
	{
		normal,
		collect,
	};
private:
	typedef void(GeneralFood::*_func)();
	void NormalUpdate();
	void CollectUpdate();
	State _state;
	std::map<State, _func> _update;

public:
	//handle �摜�n���h��
	//pos ���W
	//vel ������΂��x�N�g��
	//status �X�e�[�^�X
	//turnAngle �񂷊p�x
	GeneralFood(int handle, const Position& pos, const Vector2& vel, Food::FoodStatus status, double turnAngle);
	~GeneralFood();

	void Update();
	void Draw(const Vector2& offset);
};

