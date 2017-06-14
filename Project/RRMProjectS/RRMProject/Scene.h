#pragma once

#include <vector>

class Scene
{
protected:

	enum class LogoIdx
	{
		GameStart,
		StageSelect,

		logoMax
	};

	LogoIdx _logoState;

public:
	Scene();
	virtual ~Scene();

	virtual bool Update() = 0;
};

