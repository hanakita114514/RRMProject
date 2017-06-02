#include "UIFactory.h"
#include "HPBar.h"

UIFactory::UIFactory()
{
}


UIFactory::~UIFactory()
{
}

UI*
UIFactory::Create()
{
	return nullptr;
}

HPBar* CreateHPBar(const Position& ownPos, HitPoint& hp)
{
	return new HPBar(ownPos, hp);
}