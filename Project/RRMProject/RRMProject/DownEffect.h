#pragma once
#include "Effect.h"

class DownEffect : public Effect
{
private:
	void AnimUV();

public:
	DownEffect(int handle, const Position& pos);
	~DownEffect();

	void Update();
	void Draw(const Vector2& offset);
};

