#pragma once
#include "Effect.h"

class UpEffect : public Effect
{
private:
	void AnimUV();

public:
	UpEffect(int handle);
	~UpEffect();

	void Update();
	void Draw(const Vector2& offset);
};

