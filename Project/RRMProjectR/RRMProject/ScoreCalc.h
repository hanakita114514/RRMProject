#pragma once

#include "Number.h"
#include <map>
#include "Vector2.h"
#include "EvaluationLogo.h"

//ÉXÉRÉAï]âø
enum class ScoreEvaluation
{
	S,
	A,
	B,
	C,
};


class ScoreCalc
{
private:
	enum class State
	{
		start,
		calc,
		evaluation,
		end,
	};
private:
	typedef void(ScoreCalc::*_func)();

	std::map<State, _func> _update;
	State _state;

	int _logoHandle;

	void StartUpdate();
	void CalcUpdate();
	void EvaluationUpdate();
	void EndUpdate();

	Position _destPos;
	Position _pos;

	std::map<ScoreEvaluation, int> _evaluationMap;

	Number _number;

	long long int _addScore;
	long long int _resultScore;
	long long int _score;
	ScoreEvaluation _evaluation;
	EvaluationLogo _evaLogo;

public:
	ScoreCalc(const Position& pos, int handle);
	~ScoreCalc();

	void Evaluation(long long int score, ScoreEvaluation se);
	void Update();

	bool IsEnd() { return _state == State::end; }
};

