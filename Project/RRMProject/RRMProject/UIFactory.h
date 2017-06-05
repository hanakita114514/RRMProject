#pragma once

#include "UI.h"
#include "HitPoint.h"

class HPBar;

class UIFactory
{
private:

public:
	UIFactory();
	~UIFactory();

	UI* Create();
};

