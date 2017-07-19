#include "AbstractSpell.h"

AbstractSpell::AbstractSpell()
{
	_comet = new Comet();
	_circleShot = new CircleShot();
	_testSpell = new TestSpell();
	_rainSpell = new RainSpell();
}


AbstractSpell::~AbstractSpell()
{
	delete _comet;
	delete _circleShot;
	delete _testSpell;
	delete _rainSpell;
}

Spell*
AbstractSpell::GetSpell(SpellType type)
{
	switch (type)
	{
	case SpellType::Comet:
	{
		return _comet;
	}
		break;
	case SpellType::CircleShot:
	{
		return _circleShot;
	}
		break;
	case SpellType::TestSpell:
	{
		return _testSpell;
	}
	case SpellType::RainSpell:
	{
		return _rainSpell;
	}
		break;
	default:
		break;
	}
}
