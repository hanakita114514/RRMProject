#pragma once

#include <vector>


enum class LogoIdx
{
	GameStart,
	StageSelect,

	logoMax
};

class Scene
{
protected:

	LogoIdx _logoState;

public:
	Scene();
	virtual ~Scene();

	virtual bool Update() = 0;
};

