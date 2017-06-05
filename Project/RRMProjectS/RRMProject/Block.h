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
	virtual ~Block();

	virtual void Initialize(Vector2 pos, int handle,Vector2 size);

	virtual void Draw(const Vector2& offset);
};

