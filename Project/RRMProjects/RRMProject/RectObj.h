#pragma once
#include "Object.h"
#include "Rect.h"

class RectObj : public Object
{
private:

protected:

	Rect _rc;

public:
	RectObj();
	~RectObj();

	void SetPos(Rect pos) { _rc = pos; }
	Position& GetPosition() { return _rc.pos; }
	Rect& GetRect() { return _rc; }
};

