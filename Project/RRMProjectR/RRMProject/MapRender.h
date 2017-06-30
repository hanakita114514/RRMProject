#pragma once
#include <vector>
#include "fmfmap.h"
#include "Block.h"

const int MAP_ARRAY_SIZE_X = 40;
const int MAP_ARRAY_SIZE_Y = 20;
const int MAP_CHIP_Y_NUM = 16;
const int EDITER_CHIP_X_NUM = 16;

using namespace std;

enum class MAP_CHIP_TYPE
{
	NONE,
	SAND,
	BLOCK1,
	BLOCK2,
	TREES_LEFTUP = 20,
	TREES_RIGHTUP,
	TREE_LEFTUP,
	TREE_RIGHTUP,
	TREES_LEFTDOWN = 36,
	TREES_RIGHTDOWN,
	TREE_LEFTDOWN,
	TREE_RIGHTDOWN,
	BRANCHES_LEFTUP = 52,
	BRANCHES_RIGHTUP,
	BRANCHE_LEFTUP,
	BRANCH_RIGHTUP,

	WOOD_BLOCK = 113,
};

typedef struct DefaultData
{
	char* mapFilePath;
	char* bgFilePath;
}D_Data;

class MapRender
{
private:

	int _checkArray[MAP_ARRAY_SIZE_Y];

	FMFHEADER _header;
	const char* _filePath;

	std::vector<std::vector<int>> _mapList;
	std::vector<unsigned char> _map;
	std::vector<Block*> _blockList;

	int _checkNum;

public:
	MapRender();
	~MapRender();

	void Initialize(const char* mapFilePath);


	void MapDraw(std::vector<Block*> &block, const Vector2 &offset);
	std::vector<std::vector<int>> GetMap() { return _mapList; }

	std::vector<Block*>& GetBlockList() { return _blockList; }
};

