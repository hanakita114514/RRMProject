#pragma once
#include "CircleShot.h"
#include "TestSpell.h"
#include "Comet.h"
#include "RainSpell.h"

enum class SpellType
{
	none,

	Comet,
	CircleShot,
	TestSpell,
	RainSpell,
};

class AbstractSpell
{
private:
	Comet* _comet;
	TestSpell* _testSpell;
	CircleShot* _circleShot;
	RainSpell* _rainSpell;

public:
	AbstractSpell();
	~AbstractSpell();

	Spell* GetSpell(SpellType type);
};

