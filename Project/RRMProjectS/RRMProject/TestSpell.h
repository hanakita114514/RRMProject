#pragma once
#include "Spell.h"

class TestSpell : public Spell
{
public:
	TestSpell();
	~TestSpell();

	void Create(Vector2 vec, Vector2 pos, Object *owner);
};

