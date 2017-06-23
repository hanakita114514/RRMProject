#pragma once
#include "Spell.h"
class Comet : public Spell
{
public:
	Comet();
	~Comet();

	void Create(Vector2 vec, Vector2 pos, Object *owner);
};

