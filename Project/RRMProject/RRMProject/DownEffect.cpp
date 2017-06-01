#include "DownEffect.h"
#include "GameTime.h"
#include <DxLib.h>

//エフェクト一つ当たりの大きさ
const int EFFECT_SIZE_W = 256;
const int EFFECT_SIZE_H = 256;

//縦列の数
const int COLUMN_NUM = 5;
const int ROW_NUM = 6;
const int EFFECT_NUM = ROW_NUM * COLUMN_NUM;

//画像のサイズ
const int IMAGE_SIZE_W = 1280;
const int IMAGE_SIZE_H = 1536;

//アニメのUV値
const Vector2 animUV[ROW_NUM][COLUMN_NUM] =
{
	{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 0), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 0), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 0), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 0), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 0), },
	{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 1), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 1), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 1), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 1), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 1), },
	{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 2), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 2), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 2), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 2), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 2), },
	{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 3), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 3), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 3), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 3), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 3), },
	{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 4), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 4), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 4), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 4), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 4), },
	{ Vector2(EFFECT_SIZE_W * 0, EFFECT_SIZE_H * 5), Vector2(EFFECT_SIZE_W * 1, EFFECT_SIZE_H * 5), Vector2(EFFECT_SIZE_W * 2, EFFECT_SIZE_H * 5), Vector2(EFFECT_SIZE_W * 3, EFFECT_SIZE_H * 5), Vector2(EFFECT_SIZE_W * 4, EFFECT_SIZE_H * 5), },
};

DownEffect::DownEffect(int handle, const Vector2& pos)
{
	_frame = 0.f;
	_handle = handle;
	_pos = pos;
}


DownEffect::~DownEffect()
{
}

void
DownEffect::AnimUV()
{
	int frame = (int)_frame;
	_uv = animUV[(frame % EFFECT_NUM) / COLUMN_NUM][frame % COLUMN_NUM];
}

void
DownEffect::Update()
{
	AnimUV();
	_frame += 1 * GameTime::Instance().GetTimeScale();
}

void
DownEffect::Draw(const Vector2& offset)
{
	Position drawPos;
	drawPos.x = _pos.x - offset.x;
	drawPos.y = _pos.y - offset.y;

	DxLib::DrawRectGraph(drawPos.x, drawPos.y, _uv.x, _uv.y,
		EFFECT_SIZE_W, EFFECT_SIZE_H, _handle, true, false);
}