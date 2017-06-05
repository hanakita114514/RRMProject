#include "GraphicLoad.h"
#include <DxLib.h>


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
		_graphMap[filePath] = DxLib::LoadGraph(filePath.c_str());
	}

	return _graphMap[filePath];
}

void 
GraphicLoad::Delete()
{
	for (auto g : _graphMap)
	{
		DeleteGraph(g.second);
	}
}