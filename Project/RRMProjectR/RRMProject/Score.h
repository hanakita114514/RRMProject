#pragma once

#include "Number.h"

class Score
{
private:
	long long int _score;
	long long int _heighScore;

	int _scoreHandle;
	int _slashHandle;
	int _koronHandle;

	Number _scoreNum;
	Number _heighNum;
public:
	Score();
	~Score();

	void Add(long long int score);
	void Draw();

	long long int GetScore() { return _score; }
	long long int GetHeighScore() { return _heighScore; }
};

