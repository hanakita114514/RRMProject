#pragma once
#include "Effect.h"

class DownEffect : public Effect
{
private:
	//戻り値 アニメーションフレームを返す
	//UVを取得する
	int AnimUV();

public:
	DownEffect(int handle, const Position& pos, const Vector2& size);
	~DownEffect();

	void Update();
	void Draw(const Vector2& offset);
};

