#pragma once
#include <vector>
#include "Vector2.h"
class Block;

const float MAP_CHIP_SIZE_X = 32;
const float MAP_CHIP_SIZE_Y = 32;
const int MAP_IMAGE_X_NUM = 8;
const int MAP_IMAGE_Y_NUM = 16;
const int MAP_IMAGE_ALL_NUM = 128;

class BlockManager
{
private:

	BlockManager();

	int _mapImage[MAP_IMAGE_X_NUM * MAP_IMAGE_Y_NUM];
	std::vector<Block*> _blockList;
public:
	~BlockManager();

	static BlockManager& Instance()
	{
		static BlockManager instance;
		return instance;
	}
	void Update();
	void Draw(const Vector2& offset);

	void Delete();

	void BlockInit(std::vector<std::vector<int>>map,int mapHeight, int mapWidth);

	std::vector<Block*>& GetBlockList() { return _blockList; }
};

