#pragma once
#include "Effect.h"

class UpEffect : public Effect
{
private:
	int AnimUV();

public:
	UpEffect(int handle, const Position& pos, const Vector2& size);
	~UpEffect();

	void Update();
	void Draw(const Vector2& offset);
};

