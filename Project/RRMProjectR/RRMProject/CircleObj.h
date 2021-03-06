#pragma once
#include "Object.h"
#include "Circle.h"

class CircleObj : public Object
{
private:

protected:
	Circle _circle;

public:
	CircleObj();
	~CircleObj();

	Circle& GetCircle() { return _circle; }
	Position& GetPosition() { return _circle.pos; }
	
	void SetPos(Vector2 pos) 
	{
		_circle.pos.x = pos.x;
		_circle.pos.y = pos.y;
	}
};

