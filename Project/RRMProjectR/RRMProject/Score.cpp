#include "Score.h"
#include "common.h"
#include <RRMLib.h>

static const float SCORE_X = 350.f;
static const float SCORE_Y = WINDOW_HEIGHT - 25.f;

static const float OFFSET_X = 30.0f;

static const float FONT_SIZE = 40.f;

Score::Score() : _scoreNum(FONT_SIZE),
_heighNum(FONT_SIZE,
	RRMLib::LoadGraph("Resource/img/UI/Number/highScore/number1.png"),64.f , 64.f)
{
	_score = 0;
	_heighScore = 114514;
	_slashHandle = RRMLib::LoadGraph("Resource/img/UI/Number/slash.png");
	_scoreHandle = RRMLib::LoadGraph("Resource/img/UI/Logo/Score.png");
	_koronHandle = RRMLib::LoadGraph("Resource/img/UI/score_koron.png");
}


Score::~Score()
{

}

void
Score::Add(long long int score)
{
	_score += score;
}

void
Score::Draw()
{
	if (_heighScore < _score)
	{
		_heighScore = _score;
	}

	RRMLib::DrawExtendGraph(0, SCORE_Y - FONT_SIZE / 2, 100, SCORE_Y + FONT_SIZE / 2, _scoreHandle, true, false);
	RRMLib::DrawExtendGraph(65, SCORE_Y - FONT_SIZE / 2 + 5, 120, SCORE_Y + FONT_SIZE / 2 + 5, _koronHandle, true, false);

	_scoreNum.Draw(_score, Position(0 + SCORE_X, SCORE_Y));

	RRMLib::DrawExtendGraph(SCORE_X + OFFSET_X - FONT_SIZE / 2, SCORE_Y - FONT_SIZE / 2,
		SCORE_X + OFFSET_X + FONT_SIZE / 2, SCORE_Y + FONT_SIZE / 2, _slashHandle, true, false);

	_heighNum.Draw(_heighScore, Position(SCORE_X + SCORE_X, SCORE_Y));
}