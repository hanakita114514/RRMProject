#include "MapRendar.h"
#include "File.h"
#include <DxLib.h>
#include <string.h>

MapRendar::MapRendar(const char* mapFilePath)
{
	DxLib::LoadDivGraph("Resource/img/MapChip1.png", MAP_IMAGE_ALL_NUM, MAP_IMAGE_X_NUM, MAP_IMAGE_Y_NUM, 32, 32, _mapImage);

	for (int i = 0; i < MAP_ARRAY_SIZE_Y; i++)
	{
		_checkArray[i] = MAP_IMAGE_X_NUM * i;
	}
	_filePath = mapFilePath;
}

MapRendar::~MapRendar()
{

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

	 BlockInit();

	return true;
}

void MapRendar::MapDraw()
{
	vector<Block>::iterator itr = _blockList.begin();
	for (itr; itr != _blockList.end(); itr++)
	{
		itr->Draw();
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

void MapRendar::BlockInit()
{
	//_blockList‚Ì‰Šú‰»---------------------------------
	unsigned int  y, x;
	y = x = 0;
		for (y = 0; y < _header.dwHeight; ++y)
		{
			for (x = 0; x < _header.dwWidth; ++x)
			{
				if (_mapList[y][x] != 0)
				{
					Block* b = new Block();
					b->Initialize(Vector2(x * MAP_CHIP_SIZE_X, y * MAP_CHIP_SIZE_Y),
											_mapImage[_mapList[y][x]],
											Vector2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y));
					_blockList.push_back(*b);
				}
			}
		}
	//--------------------------------------------------
}

