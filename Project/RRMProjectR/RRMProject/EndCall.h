#pragma once


#include <map>
class EndCall
{
	enum class State : unsigned int
	{
		start,
		end,
	};
private:
	int _filterHandle;
	int _rogoHandle;

	typedef void (EndCall::*_func)();
	State _state;
	std::map<State, _func> _update;
	void StartUpdate();
	void EndUpdate();

public:
	EndCall();
	~EndCall();

	void Update();
};

