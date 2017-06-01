#pragma once

#include "UI.h"


class UIFactory
{
private:

public:
	UIFactory();
	~UIFactory();

	UI* Create();
};

