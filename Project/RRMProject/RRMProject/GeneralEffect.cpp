#include "GeneralEffect.h"
#include "GameTime.h"
#include <DxLib.h>
#include <vector>

GeneralEffect::GeneralEffect(int handle, const Position& pos,
	int imageSizeX, int imageSizeY, int rowDivNum, int columnDivNum) :
	IMAGE_SIZE_H(imageSizeY), IMAGE_SIZE_W(imageSizeX), ROW_NUM(rowDivNum), COLUMN_NUM(columnDivNum),
	EFFECT_NUM(ROW_NUM * COLUMN_NUM), EFFECT_SIZE_H(IMAGE_SIZE_H / ROW_NUM), EFFECT_SIZE_W(IMAGE_SIZE_W / COLUMN_NUM)
{
	_frame = 0.f;
	_handle = handle;
	_pos = pos;
}


GeneralEffect::~GeneralEffect()
{
}

void 
GeneralEffect::AnimUV()
{
	std::vector<Vector2> animUV(ROW_NUM * COLUMN_NUM);

	for (int i = 0; i < animUV.size(); i++)
	{
		animUV[i] = Vector2(EFFECT_SIZE_W * (i % COLUMN_NUM), EFFECT_SIZE_H * (i / COLUMN_NUM));
	}

	int frame = (int)_frame;

	_uv = animUV[frame % EFFECT_NUM];
}

void 
GeneralEffect::Update()
{
	AnimUV();
	_frame += 1 * GameTime::Instance().GetTimeScale();
}

void 
GeneralEffect::Draw(const Vector2& offset)
{
	Position drawPos;
	drawPos.x = _pos.x - offset.x;
	drawPos.y = _pos.y - offset.y;

	DxLib::DrawRectGraph(drawPos.x, drawPos.y, _uv.x, _uv.y,
		EFFECT_SIZE_W, EFFECT_SIZE_H, _handle, true, false);
}