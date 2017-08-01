#pragma once

#include "RectObj.h"
#include "Camera.h"

enum class FoodType
{
	none,
	banana,
	beaf,
	bread,
	cake,
	chikuwa,
	choko_corone,
	corn,
	dashimaki,
	donut,
	ketchup,
	kinoko,
	mayonnaise,
	meron_bread,
	onigiri,
	pearch,
	pepper,
	salt,
	siitake,
	tomato,
	tori_karaage,

	num,
};

class Food	: public RectObj
{
public:
	struct FoodStatus
	{
		int pow;
		int speed;
		int defense;
	};
protected:
	FoodStatus _fs;

	double _angle;			//向いてる角度
	double _turnAngle;		//回す角度
	long long _score;		//スコア
	float _friction;

	bool _deleteFlag;
	bool _collectFlag;

	Vector2 _vel;

	void DistanceAttenuation();
	void Gravity();

	bool _hitGround;

public:
	Food();
	virtual ~Food();

	virtual void Update() = 0;
	virtual void Draw(const Vector2& offset) = 0;

	void ScreenLimit(Camera& camera);

	void Collect(const Position& pos);

	virtual FoodStatus GetFoodStatus();

	virtual void Hit(Player* other);
	virtual void Hit(Block* other);

	void Destory() { _deleteFlag = true; }
	bool IsDelete() { return _deleteFlag; }
	bool IsCollect() { return _collectFlag; }

	long long int GetScore() { return _score; }

};

