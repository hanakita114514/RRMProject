#pragma once
#include "RectObj.h"
class Block : public RectObj
{
	enum class BlockType
	{

	};
private:

protected:
	ObjectType _objType;
public:
	Block();
	~Block();

	void Initialize(Vector2 pos, int handle,Vector2 size);

	void Draw();
};

