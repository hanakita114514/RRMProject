#pragma once

#include "RRMCommon.h"
#include <list>

class GraphList
{
private:
	std::list<DrawingStructure> _drawList;

	GraphList();
	GraphList(const GraphList&);
	GraphList& operator = (const GraphList&);

public:
	~GraphList();

	static GraphList& Instance()
	{
		static GraphList instance;
		return instance;
	}

	void Add(DrawingStructure& ds);
	void Draw();
};

