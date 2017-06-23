#pragma once
#include "Vector2.h"
#include "Circle.h"
#include "Object.h"
#include <vector>

class Spell
{
private:

protected:
	Vector2 _vec,_pos;
	float _freamCnt;

	std::vector<Bullet*> list;

	int bCnt;
	bool _shotFlag;

	void AddList(Bullet* bullet);
	void DeleteList();
	void Shot();

	Bullet* firstBullet;
public:
	Spell();
	~Spell();

	virtual void Create(Vector2 vec, Vector2 pos, Object* owner) = 0;
};

