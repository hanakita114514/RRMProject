#pragma once


#include <map>
class Logo;

class EndCall
{
	enum class State : unsigned int
	{
		start,
		startWait,
		middle,
		end,
	};
private:
	int _filterHandle;

	typedef void (EndCall::*_func)();
	State _state;
	std::map<State, _func> _update;
	void StartUpdate();
	void StartWaitUpdate();
	void MiddleUpdate();
	void EndUpdate();

	int _frame;

	float _height;

	Logo* _logo;

public:
	EndCall();
	~EndCall();

	void Update();
	bool IsEnd() { return _state == State::end; }
};

