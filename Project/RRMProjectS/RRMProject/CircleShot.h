#pragma once
#include "Spell.h"

class CircleShot : public Spell
{
public:
	CircleShot();
	~CircleShot();

	void Create(Vector2 vec, Vector2 pos, Object *owner);
};

