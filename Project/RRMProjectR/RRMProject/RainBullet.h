#pragma once
#include "Bullet.h"
#include <map>

class RainBullet : public Bullet
{
private:
	enum class State
	{
		start,
		fall,
	};
private:
	typedef void(RainBullet::*_func)();

	State _state;
	std::map<State, _func> _update;
	void StartUpdate();
	void FallUpdate();

	float _repulsion;		//”½”­

	Vector2 _vec;

	int _startCnt;

public:
	RainBullet(int handle);
	~RainBullet();

	void Initialize(const Position& pos, Vector2 vec, ObjectType type);
	void Update();
	void Draw(const Vector2& offset);
	void Hit(Block* other);
};

