#include "Result.h"
#include <RRMLib.h>
#include "common.h"
#include "Logo.h"
#include "ScoreCalc.h"
#include "GraphicLoad.h"


Result::Result(Score& score, HitPoint& playerHP, Timer& time, Combo& combo) : _score(score),
_playerHP(playerHP), _time(time), _combo(combo)
{
	_handle = GraphicLoad::Instance().LoadGraph("Resource/img/BackGround/fade.png");

	int logoHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/Logo/Result2.png");

	_update[State::init] = &Result::InitUpdate;
	_update[State::start] = &Result::StartUpdate;
	_update[State::middle] = &Result::MiddleUpdate;
	_update[State::life] = &Result::LifeUpdate;
	_update[State::end] = &Result::EndUpdate;
	_state = State::init;

	_logo = new Logo(logoHandle, Position(WINDOW_WIDTH / 2, 100));

	int lifeHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/Life.png");
	int comboHandle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/Logo/combo.png");

	int i = playerHP.GetHitPoint();
	_lifeScore = new ScoreCalc(Position(300, 200), lifeHandle);
	_comboScore = new ScoreCalc(Position(300, 300), comboHandle);

	long long int tScore;
	Times times = time.GetTime();
	tScore = 30000 - times.millisec;
	tScore = tScore < 0 ? 0 : tScore;

	_timeScore = new ScoreCalc(Position(100, 200),lifeHandle);

	_bonus = playerHP.GetHitPoint() + combo.GetMaxCombo() + tScore;
}


Result::~Result()
{
	delete _logo;
	delete _lifeScore;
	delete _comboScore;
	delete _timeScore;
}

void
Result::InitUpdate()
{
	LifeEvaluation();
	_comboScore->Evaluation(_combo.GetMaxCombo(), ScoreEvaluation::S);
	_timeScore->Evaluation(0, ScoreEvaluation::S);
	_state = State::start;
}

void 
Result::StartUpdate()
{
	_endCall.Update();

	if (_endCall.IsEnd())
	{
		_state = State::middle;
	}
}

void
Result::MiddleUpdate()
{
	_endCall.Update();
	_logo->Update();
	if (_logo->IsEnd())
	{
		_state = State::life;
	}
}

void
Result::LifeUpdate()
{
	_endCall.Update();
	_logo->Update();
	_lifeScore->Update();

	if (_lifeScore->IsEnd())
	{
		_state = State::end;
	}
}

void 
Result::EndUpdate()
{
	_endCall.Update();
	_logo->Update();
	_lifeScore->Update();
	_comboScore->Update();
	_time.Draw(Position(500, 500), 64.0f);
}

void 
Result::Update()
{
	(this->*_update[_state])();
}

bool
Result::IsEnd()
{
	return _state == State::end;
}

void 
Result::LifeEvaluation()
{
	int hp = _playerHP.GetHitPoint();
	ScoreEvaluation se;

	if (hp >= 800)
	{
		se = ScoreEvaluation::S;
	}
	else if (hp >= 500)
	{
		se = ScoreEvaluation::A;

	}
	else if (hp >= 300)
	{
		se = ScoreEvaluation::B;

	}
	else
	{
		se = ScoreEvaluation::C;
	}

	_lifeScore->Evaluation(hp, se);
}