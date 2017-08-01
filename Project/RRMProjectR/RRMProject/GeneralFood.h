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
	//handle 画像ハンドル
	//pos 座標
	//vel 吹っ飛ばしベクトル
	//status ステータス
	//turnAngle 回す角度
	GeneralFood(int handle, const Position& pos, const Vector2& vel, Food::FoodStatus status, double turnAngle);
	~GeneralFood();

	void Update();
	void Draw(const Vector2& offset);
};

