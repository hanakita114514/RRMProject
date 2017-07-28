#pragma once

#include <map>
#include "EndCall.h"
#include "Score.h"
#include "Combo.h"
#include "HitPoint.h"
#include "Timer.h"

class Logo;
class ScoreCalc;

class Result
{
private:
	enum class State
	{
		init,
		start,
		middle,
		life,
		end,
	};
private:
	int _handle;
	int _alpha;
	int _characterImage;

	typedef void (Result::*_func)();
	std::map<State, _func> _update;

	void InitUpdate();
	void StartUpdate();
	void MiddleUpdate();
	void LifeUpdate();
	void ImageUpdate();
	void EndUpdate();

	State _state;

	EndCall _endCall;

	Logo* _logo;

	ScoreCalc* _lifeScore;
	ScoreCalc* _timeScore;
	ScoreCalc* _comboScore;

	Score& _score;
	HitPoint& _playerHP;
	Timer& _time;
	Combo& _combo;

	int _maxCombo;

	long long int _bonus;

	void LifeEvaluation();

public:
	Result(Score& score, HitPoint& playerHP, Timer& time, Combo& combo);
	~Result();

	void Update();

	bool IsEnd();
};

