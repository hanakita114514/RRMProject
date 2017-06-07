#include "AbstractSpell.h"



AbstractSpell::AbstractSpell()
{
	comet = new Comet();
	circleShot = new CircleShot();
	testSpell = new TestSpell();
}


AbstractSpell::~AbstractSpell()
{
	delete comet;
	delete circleShot;
	delete testSpell;
}

Spell*
AbstractSpell::GetSpell(SpellType type)
{
	switch (type)
	{
	case SpellType::Comet:
	{
		return comet;
	}
		break;
	case SpellType::CircleShot:
	{
		return circleShot;
	}
		break;
	case SpellType::TestSpell:
	{
		return testSpell;
	}
		break;
	default:
		break;
	}
}
