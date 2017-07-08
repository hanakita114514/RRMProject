#pragma once
#include "Scene.h"

#include <map>

class Input;

class OfficialScene : public Scene
{
private:
	enum class State : unsigned int
	{
		start,
		middle,
		end,
	};
private:

	int _logoHandle;

	typedef void (OfficialScene::*_func)();
	std::map<State, _func> _update;

	void StartUpdate();
	void MiddleUpdate();
	void EndUpdate();

	State _state;
	int _frame;

	Input* _input;

public:
	OfficialScene();
	~OfficialScene();

	bool Update();
};

