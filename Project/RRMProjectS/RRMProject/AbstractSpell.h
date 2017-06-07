#pragma once
#include "CircleShot.h"
#include "TestSpell.h"
#include "Comet.h"

enum class SpellType
{
	Comet,
	CircleShot,
	TestSpell
};

class AbstractSpell
{
	Comet* comet;
	TestSpell* testSpell;
	CircleShot* circleShot;
public:
	AbstractSpell();
	~AbstractSpell();

	Spell* GetSpell(SpellType type);

};

