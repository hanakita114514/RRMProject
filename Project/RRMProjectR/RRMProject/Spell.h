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
	float _frameCnt;

	std::vector<Bullet*> list;

	int bCnt;
	bool _shotFlag;

	void AddList(Bullet* bullet);
	void DeleteList();
	void Shot();

	Bullet* firstBullet;
	bool _isEnd;
public:
	Spell();
	~Spell();

	virtual void Create(Vector2 vec, Vector2 pos, Object* owner) = 0;
	virtual void Update();

	bool IsEnd() { return _isEnd;}
};

