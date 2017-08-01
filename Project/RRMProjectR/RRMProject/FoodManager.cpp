#include "FoodManager.h"
#include <time.h>
#include <math.h>

FoodManager::FoodManager()
{
	srand(time(NULL));
}


FoodManager::~FoodManager()
{
}

void 
FoodManager::Update()
{
	for (auto& f : _foodList)
	{
		f->Update();
	}

	DeleteUpdate();
}

void 
FoodManager::Draw(const Vector2& offset)
{
	for (auto& f : _foodList)
	{
		f->Draw(offset);
	}
}

void 
FoodManager::ScreenLimit(Camera& camera)
{
	for (auto& f : _foodList)
	{
		f->ScreenLimit(camera);
	}
}

void 
FoodManager::Create(FoodType type, const Position& pos, const Vector2& vel, double turnAngle)
{
	_foodList.push_back(_factory.Create(type, pos, vel, turnAngle));
}

void 
FoodManager::RandomCreate(const Position& pos)
{
	FoodType type = (FoodType)(rand() % ((int)FoodType::num - 1) + 1);
	Vector2 vel;
	vel.x = rand() % 20 - 10;
	vel.y = rand() % 20 - 10;
	double angle = rand() % 100;

	_foodList.push_back(_factory.Create(type, pos, vel, angle));
}

void 
FoodManager::DeleteUpdate()
{
	std::vector<Food*>::iterator it = _foodList.begin();
	for (; it != _foodList.end();)
	{
		if ((*it)->IsDelete())
		{
			delete(*it);
			*it = nullptr;
			it = _foodList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void 
FoodManager::AllDelete()
{
	std::vector<Food*>::iterator itr;
	itr = _foodList.begin();
	for (itr; itr != _foodList.end();)
	{
		delete (*itr);
		*itr = nullptr;
		itr = _foodList.erase(itr);
	}
}

void 
FoodManager::Collect(const Position& pos)
{
	for (auto& f : _foodList)
	{
		f->Collect(pos);
	}
}