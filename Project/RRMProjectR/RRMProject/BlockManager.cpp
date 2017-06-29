#include "BlockManager.h"
#include "Block.h"
#include "NormalBlock.h"
#include "ThroughBlock.h"
#include <RRMLib.h>

BlockManager::BlockManager()
{
	RRMLib::LoadDivGraph("Resource/img/MapChip1.png", MAP_IMAGE_ALL_NUM, MAP_IMAGE_X_NUM, MAP_IMAGE_Y_NUM, 32, 32, _mapImage);

}


BlockManager::~BlockManager()
{
}

void
BlockManager::Update()
{
}

void 
BlockManager::Draw(const Vector2& offset)
{
	for (auto& a : _blockList)
	{
		a->Draw(offset);
	}
}

void 
BlockManager::BlockInit(std::vector<unsigned char> buf,int mapHeight, int mapWidth)
{
	int y, x;
	y = x = 0;
	Block* b = nullptr;

	int mapMax = mapHeight * mapWidth;

	for (y;y < mapMax;++y)
	{
		if ((int)buf[y] != (int)BlockType::none)
		{
			switch ((int)buf[y])
			{
			case (int)BlockType::throughBlock1:
			case (int)BlockType::throughBlock2:
			case (int)BlockType::throughBlock3:
			case (int)BlockType::throughBlock4:
			case (int)BlockType::throughBlock5:
			case (int)BlockType::throughBlock6:
			{
				b = new ThroughBlock();
				b->Initialize(Vector2((y % mapWidth) * MAP_CHIP_SIZE_X, (y / mapWidth)* MAP_CHIP_SIZE_Y),
					_mapImage[(int)buf[y]],
					Vector2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y),
					BlockType::throughBlock1);
			}
			break;
			default:
			{
				b = new NormalBlock();
				b->Initialize(Vector2((y % mapWidth) * MAP_CHIP_SIZE_X, (y / mapWidth)* MAP_CHIP_SIZE_Y),
					_mapImage[(int)buf[y]],
					Vector2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y),
					BlockType::normalBlock);
			}
			break;
			}
			_blockList.push_back(b);

		}
	}
	int i = 0;
}

void
BlockManager::Delete()
{
	auto itr = _blockList.begin();

	for (itr; itr != _blockList.end();)
	{
		delete (*itr);
		*itr = nullptr;
		itr = _blockList.erase(itr);
	}
}
