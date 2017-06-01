#include "UpEffect.h"
#include "GameTime.h"
#include <DxLib.h>

//エフェクト一つ当たりの大きさ
const int EFFECT_SIZE_W = 256;
const int EFFECT_SIZE_H = 256;

//縦列の数
const int COLUMN_NUM = 5;
const int ROW_NUM = 6;

//画像のサイズ
const int IMAGE_SIZE_W = 1280;
const int IMAGE_SIZE_H = 1536;

UpEffect::UpEffect(int handle)
{
	_frame = 0.f;
	_handle = handle;
}


UpEffect::~UpEffect()
{
}


void 
UpEffect::Update()
{
	_frame += 1 * GameTime::Instance().GetTimeScale();
}

void 
UpEffect::AnimUV()
{
	const Vector2 animTable[ROW_NUM][COLUMN_NUM] =
	{
		{Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 0),Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 0), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 0), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 0), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 0), },
		{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 1), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 1), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 1), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 1), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 1), },
		{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 2), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 2), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 2), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 2), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 2), },
		{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 3), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 3), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 3), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 3), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 3), },
		{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 4), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 4), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 4), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 4), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 4), },
		{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 5), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 5), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 5), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 5), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 5), },
	};
}

void 
UpEffect::Draw(const Vector2& offset)
{
	DxLib::DrawRectGraph(0, 0, 0 * EFFECT_SIZE_W, 0 * EFFECT_SIZE_H,
		EFFECT_SIZE_W, EFFECT_SIZE_H, _handle, true, false);
}