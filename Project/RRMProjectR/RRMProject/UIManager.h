#pragma once

#include "UIFactory.h"
#include <vector>

class UIManager
{
private:
	UIFactory _uiFactory;

	std::vector<UI*> _uiList;

public:
	UIManager();
	~UIManager();

	void Create();
	void Draw();
};

