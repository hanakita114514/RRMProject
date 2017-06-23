#include "MapRendar.h"
#include "File.h"
#include <RRMLib.h>
#include <string.h>
#include "ThroughBlock.h"
#include "NormalBlock.h"
#include "BlockManager.h"

MapRendar::MapRendar()
{
}

MapRendar::~MapRendar()
{

}

void
MapRendar::Initialize(const char* mapFilePath)
{

	for (int i = 0; i < MAP_ARRAY_SIZE_Y; i++)
	{
		_checkArray[i] = MAP_IMAGE_X_NUM * i;
	}

	_filePath = mapFilePath;
}

bool MapRendar::MapLoad()
{
	File* file = new File(_filePath);

	bool err = file->Initialize(FILE_INIT_TYPE::FILE_READ);
	if (err != true)
	{
		return false;
	}

	 file->FileLoad(_header,_mapList);

	 NomalizeArray();

	 BlockManager::Instance().BlockInit(_mapList, _header.dwHeight, _header.dwWidth);

	 delete file;

	return true;
}

void MapRendar::MapDraw(const Vector2& offset)
{
	for (auto b : _blockList)
	{
		b->Draw(offset);
	}
}

void MapRendar::NomalizeArray()
{
	unsigned int  y, x;
	 y = x = 0;
		for (y = 0; y < _header.dwHeight; ++y)
		{
			for (x = 0; x < _header.dwWidth; ++x)
			{
				_checkNum = _mapList[y][x] / MAP_CHIP_X_NUM;
				_mapList[y][x] = _mapList[y][x] - _checkArray[_checkNum];
			}
		}
}
