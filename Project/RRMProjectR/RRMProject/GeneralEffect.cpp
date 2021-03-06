#include "GeneralEffect.h"
#include "GameTime.h"
#include <RRMLib.h>
#include <vector>

GeneralEffect::GeneralEffect(int handle, const Position& pos,
	int imageSizeX, int imageSizeY, int rowDivNum, int columnDivNum, 
	float speed, const Vector2& size, bool isLoop) :
	IMAGE_SIZE_H(imageSizeY), IMAGE_SIZE_W(imageSizeX), ROW_NUM(rowDivNum), COLUMN_NUM(columnDivNum),
	EFFECT_NUM(ROW_NUM * COLUMN_NUM), EFFECT_SIZE_H(IMAGE_SIZE_H / ROW_NUM), EFFECT_SIZE_W(IMAGE_SIZE_W / COLUMN_NUM)
{
	_frame = 0.f;
	_speed = speed;
	_handle = handle;
	_pos = pos;

	_size = size;

	_animUV.resize(ROW_NUM * COLUMN_NUM);
	for (int i = 0; i < _animUV.size(); i++)
	{
		_animUV[i] = Vector2((float)(EFFECT_SIZE_W * (i % COLUMN_NUM)), (float)(EFFECT_SIZE_H * (i / COLUMN_NUM)));
	}

	if (isLoop)
	{
		_update = &GeneralEffect::LoopUpdate;
	}
	else
	{
		_update = &GeneralEffect::NormalUpdate;
	}
}


GeneralEffect::~GeneralEffect()
{
}

int 
GeneralEffect::AnimUV()
{
	int animFrame = (int)(_frame / _speed);

	_uv = _animUV[animFrame % EFFECT_NUM];

	return animFrame;
}

void 
GeneralEffect::NormalUpdate()
{
	int animFrame;
	animFrame = AnimUV();
	_frame += 1 * GameTime::Instance().GetTimeScale();
	if (animFrame >= EFFECT_NUM)
	{
		_deleteFlag = true;
	}
}

void 
GeneralEffect::LoopUpdate()
{
	int animFrame;
	animFrame = AnimUV();
	_frame += 1 * GameTime::Instance().GetTimeScale();

}

void 
GeneralEffect::Update()
{
	(this->*_update)();
}

void 
GeneralEffect::Draw(const Vector2& offset)
{
	Position drawPos;
	drawPos.x = _pos.x - offset.x - (EFFECT_SIZE_W / 2) * _size.x;
	drawPos.y = _pos.y - offset.y - (EFFECT_SIZE_H / 2) * _size.y;

	//RRMLib::DrawRectGraph(drawPos.x, drawPos.y, _uv.x, _uv.y,
	//	EFFECT_SIZE_W, EFFECT_SIZE_H, _handle, true, false);

	RRMLib::DrawRectExtendGraph(drawPos.x, drawPos.y, drawPos.x + EFFECT_SIZE_W * _size.x, drawPos.y + EFFECT_SIZE_H * _size.y,
		(int)_uv.x, (int)_uv.y, (int)EFFECT_SIZE_W, (int)EFFECT_SIZE_H, _handle, true, false);
}