#pragma once

#include "Food.h"
#include "FoodFactory.h"
#include <vector>
#include "Camera.h"

class FoodManager
{
private:
	std::vector<Food*> _foodList;

	FoodFactory _factory;

public:
	FoodManager();
	~FoodManager();

	void Update();
	void Draw(const Vector2& offset);
	void ScreenLimit(Camera& camera);

	void DeleteUpdate();
	void AllDelete();

	void Create(FoodType type, const Position& pos, const Vector2& vel, double turnAngle);
	void RandomCreate(const Position& pos);
	void Collect(const Position& pos);

	std::vector<Food*> GetFoodList() { return _foodList;}
};

