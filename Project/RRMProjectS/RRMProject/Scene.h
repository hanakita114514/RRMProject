#pragma once

#include <vector>

class Scene
{
protected:

public:
	Scene();
	virtual ~Scene();

	virtual bool Update() = 0;
};

