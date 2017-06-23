#pragma once
#include "Block.h"

class NormalBlock : public Block
{
public:
	NormalBlock();
	~NormalBlock();

	void Initialize(Vector2 pos, int handle, Vector2 size, BlockType type);
	void Draw(const Vector2& offset);
};

 