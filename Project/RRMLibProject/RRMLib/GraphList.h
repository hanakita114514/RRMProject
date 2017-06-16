#pragma once

#include "RRMCommon.h"
#include <list>

class GraphList
{
private:
	std::list<DrawingStructure> _drawList;

public:
	GraphList();
	~GraphList();

	void Add(DrawingStructure& ds);
	void Draw();
};

