#include "AbstractSpell.h"

AbstractSpell::AbstractSpell()
{
	_comet = new Comet();
	_circleShot = new CircleShot();
	_testSpell = new TestSpell();
	_rainSpell = new RainSpell();
	_drop = new DropShot();
}


AbstractSpell::~AbstractSpell()
{
	delete _comet;
	delete _circleShot;
	delete _testSpell;
	delete _rainSpell;
	delete _drop;
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
	case SpellType::Drop:
	{
		return _drop;
	}
	break;
	default:
		break;
	}
}
