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

bool MapRender::MapLoad()
{
	File* file = new File(_filePath);

	bool err = file->Initialize(FILE_INIT_TYPE::FILE_READ);
	if (err != true)
	{
		return false;
	}

	file->FileRead(&_header, sizeof(_header), 1);

	_map.resize(_header.dwHeight * _header.dwWidth);

	file->FileRead(&_map[0], _map.size(), 1);

	 NomalizeArray();

	 BlockManager::Instance().BlockInit(_map, _header.dwHeight, _header.dwWidth);

	 delete file;

	return true;
}

void MapRender::MapDraw(const Vector2& offset)
{
	for (auto b : _blockList)
	{
		b->Draw(offset);
	}
}

void 
MapRender::MapDraw(std::vector<Block*> &block, const Vector2 &offset)
{
	for (auto b : block)
	{
		b->Draw(offset);
	}
}

void MapRender::NomalizeArray()
{
	//unsigned int  y, x;
	// y = x = 0;

	// for (y; y < _header.dwHeight * _header.dwWidth; ++y)
	// {
	//	 _checkNum = _map[y] / MAP_CHIP_X_NUM;
	//	 _map[y] = (int)(_map[y] - _checkArray[_checkNum]);
	// }
}
