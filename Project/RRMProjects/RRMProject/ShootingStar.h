#pragma once
#include "Spell.h"

class ShootingStar : public Spell
{
public:
	ShootingStar();
	~ShootingStar();

	void Create(Vector2 vec, Vector2 pos, Object* owner);
};

