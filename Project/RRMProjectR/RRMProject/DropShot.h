#pragma once
#include "Spell.h"
class DropShot : public Spell
{
public:
	DropShot();
	~DropShot();

	int _bulletNum;

	void Create(Vector2 vec, Vector2 pos, Object* owner);
};

