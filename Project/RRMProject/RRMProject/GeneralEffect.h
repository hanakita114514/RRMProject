#pragma once
#include "Effect.h"

class GeneralEffect : public Effect
{
private:
	//画像のサイズ
	const int IMAGE_SIZE_W;
	const int IMAGE_SIZE_H;
	//縦列の数
	const int COLUMN_NUM;
	const int ROW_NUM;
	const int EFFECT_NUM;
	//エフェクト一つ当たりの大きさ
	const int EFFECT_SIZE_W;
	const int EFFECT_SIZE_H;

private:
	void AnimUV();

public:
	GeneralEffect(int handle, const Position& pos, 
		int imageSizeX, int imageSizeY, int rowDivNum, int columnDivNum);
	~GeneralEffect();

	void Update();
	void Draw(const Vector2& offset);
};

