#include "GraphicLoad.h"
#include <RRMLib.h>


GraphicLoad::GraphicLoad()
{
}


GraphicLoad::~GraphicLoad()
{
}

int 
GraphicLoad::LoadGraph(const std::string& filePath)
{
	if (_graphMap.find(filePath) == _graphMap.end())
	{
		_graphMap[filePath] = RRMLib::LoadGraph(filePath.c_str());
	}

	return _graphMap[filePath];
}

void 
GraphicLoad::Delete()
{
	for (auto g : _graphMap)
	{
		RRMLib::DeleteGraph(g.second);
	}
}