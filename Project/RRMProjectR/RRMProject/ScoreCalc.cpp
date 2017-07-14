#include "ScoreCalc.h"
#include <RRMLib.h>
#include "GraphicLoad.h"

static const float SPEED = 50.0f;
static const float START_OFFSET = 500.0f;

static const float WIDTH = 128.0f;
static const float HEIGHT = 64.0f;
static const float LOGO_OFFSET = WIDTH * 4;
static const float EVA_OFFSET = LOGO_OFFSET * 1.2f;

ScoreCalc::ScoreCalc(const Position& pos, int handle) : _number(64.0f)
{
	_state = State::start;

	_update[State::start] = &ScoreCalc::StartUpdate;
	_update[State::calc] = &ScoreCalc::CalcUpdate;
	_update[State::evaluation] = &ScoreCalc::EvaluationUpdate;
	_update[State::end] = &ScoreCalc::EndUpdate;

	_destPos = pos;
	_pos = Position(_destPos.x - START_OFFSET, _destPos.y);

	_logoHandle = handle;

	_evaluationMap[ScoreEvaluation::S] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/S.png");
	_evaluationMap[ScoreEvaluation::A] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/A.png");
	_evaluationMap[ScoreEvaluation::B] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/B.png");
	_evaluationMap[ScoreEvaluation::C] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/C.png");

}

ScoreCalc::~ScoreCalc()
{
}

void
ScoreCalc::Evaluation(long long int score, ScoreEvaluation se)
{
	_score = score;
	_evaluation = se;

	_addScore = _score * 0.01f;
	if (_addScore <= 0)
	{
		_addScore = 1;
	}
	_resultScore = 0;
}

void 
ScoreCalc::StartUpdate()
{
	_pos.x += SPEED;

	RRMLib::DrawExtendGraph(_pos.x - WIDTH / 2, _pos.y - HEIGHT / 2,
		_pos.x + WIDTH / 2, _pos.y + HEIGHT / 2, _logoHandle);
	_number.Draw(0, Position(_pos.x + LOGO_OFFSET , _pos.y));

	if (_destPos.x < _pos.x)
	{
		_pos.x = _destPos.x;
		_state = State::calc;
	}
}

void 
ScoreCalc::CalcUpdate()
{
	_resultScore += _addScore;
	if (_resultScore >= _score)
	{
		_state = State::evaluation;
		_resultScore = _score;
	}
	RRMLib::DrawExtendGraph(_pos.x - WIDTH / 2, _pos.y - HEIGHT / 2,
		_pos.x + WIDTH / 2, _pos.y + HEIGHT / 2, _logoHandle);
	_number.Draw(_resultScore, Position(_pos.x + LOGO_OFFSET, _pos.y));

}

void 
ScoreCalc::EvaluationUpdate()
{
	RRMLib::DrawExtendGraph(_pos.x - WIDTH / 2, _pos.y - HEIGHT / 2,
		_pos.x + WIDTH / 2, _pos.y + HEIGHT / 2, _logoHandle);
	_number.Draw(_resultScore, Position(_pos.x + LOGO_OFFSET, _pos.y));
	_evaLogo.Draw(_evaluationMap[_evaluation], Position(_pos.x + EVA_OFFSET, _pos.y));

	if (_evaLogo.IsEnd())
	{
		_state = State::end;
	}
}

void 
ScoreCalc::EndUpdate()
{
	RRMLib::DrawExtendGraph(_pos.x - WIDTH / 2, _pos.y - HEIGHT / 2,
		_pos.x + WIDTH / 2, _pos.y + HEIGHT / 2, _logoHandle);
	_number.Draw(_resultScore, Position(_pos.x + LOGO_OFFSET, _pos.y));
	_evaLogo.Draw(_evaluationMap[_evaluation], Position(_pos.x + EVA_OFFSET, _pos.y));
}

void
ScoreCalc::Update()
{
	(this->*_update[_state])();
}