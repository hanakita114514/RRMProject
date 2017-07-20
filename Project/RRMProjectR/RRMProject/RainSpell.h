#pragma once
#include "Spell.h"

class RainSpell : public Spell
{
private:
	int _offset;

public:
	RainSpell();
	~RainSpell();

	void Create(Vector2 vec, Vector2 pos, Object* owner);
};

