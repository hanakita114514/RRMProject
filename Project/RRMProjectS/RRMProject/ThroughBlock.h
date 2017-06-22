#pragma once
#include "Block.h"
class ThroughBlock : public Block
{
public:
	ThroughBlock();
	~ThroughBlock();

	void Initialize(Vector2 pos, int handle, Vector2 size, BlockType type);

	void Draw(const Vector2& offset);
};

