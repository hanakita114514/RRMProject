#include "MapRender.h"
#include "File.h"
#include <RRMLib.h>
#include <string.h>
#include "ThroughBlock.h"
#include "NormalBlock.h"
#include "BlockManager.h"

MapRender::MapRender()
{
}

MapRender::~MapRender()
{

}

void
MapRender::Initialize(const char* mapFilePath)
{
	for (int i = 0; i < MAP_ARRAY_SIZE_Y; i++)
	{
		_checkArray[i] = MAP_IMAGE_X_NUM * i;
	}

	_filePath = mapFilePath;
}


void 
MapRender::MapDraw(std::vector<Block*> &block, const Vector2 &offset)
{
	for (auto b : block)
	{
		b->Draw(offset);
	}
}
