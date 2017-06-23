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
BlockManager::BlockInit(std::vector<std::vector<int>>map,int mapHeight, int mapWidth)
{
	int y, x;
	y = x = 0;
	Block* b = nullptr;
	for (y = 0; y < mapHeight; ++y)
	{
		for (x = 0; x < mapWidth; ++x)
		{
			if (map[y][x] != (int)BlockType::none)
			{
				switch (map[y][x])
				{
				case (int)BlockType::throughBlock1:
				case (int)BlockType::throughBlock2:
				case (int)BlockType::throughBlock3:
				case (int)BlockType::throughBlock4:
				case (int)BlockType::throughBlock5:
				case (int)BlockType::throughBlock6:
				{
					b = new ThroughBlock();
					b->Initialize(Vector2(x * MAP_CHIP_SIZE_X, y * MAP_CHIP_SIZE_Y),
						_mapImage[map[y][x]],
						Vector2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y),
						BlockType::throughBlock1);
				}
				break;
				default:
				{
					b = new NormalBlock();
					b->Initialize(Vector2(x * MAP_CHIP_SIZE_X, y * MAP_CHIP_SIZE_Y),
						_mapImage[map[y][x]],
						Vector2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y),
						BlockType::normalBlock);
				}
				}
				_blockList.push_back(b);
			}
		}
	}

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
