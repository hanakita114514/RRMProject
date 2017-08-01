#pragma once
#include "CircleShot.h"
#include "TestSpell.h"
#include "Comet.h"
#include "RainSpell.h"
#include "DropShot.h"

enum class SpellType
{
	none,

	Comet,
	CircleShot,
	TestSpell,
	RainSpell,
	Drop,
};

class AbstractSpell
{
private:
	Comet* _comet;
	TestSpell* _testSpell;
	CircleShot* _circleShot;
	RainSpell* _rainSpell;
	DropShot* _drop;

public:
	AbstractSpell();
	~AbstractSpell();

	Spell* GetSpell(SpellType type);
};

