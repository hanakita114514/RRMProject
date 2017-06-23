#pragma once
#include "RectObj.h"

enum class BlockType
{
	none,
	normalBlock,

	throughBlock1 = 84,
	throughBlock2,
	throughBlock3,
	throughBlock4 = 92,
	throughBlock5,
	throughBlock6
};


class Block : public RectObj
{
private:
protected:

	BlockType _blockType;

	ObjectType _objType;
public:
	Block();
	virtual ~Block();

	virtual void Initialize(Vector2 pos, int handle, Vector2 size,BlockType type) = 0;

	virtual void Draw(const Vector2& offset) = 0;

	BlockType GetBlockType() { return _blockType; }
};

