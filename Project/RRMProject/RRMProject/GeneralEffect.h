#pragma once
#include "Effect.h"

class GeneralEffect : public Effect
{
private:
	//�摜�̃T�C�Y
	const int IMAGE_SIZE_W;
	const int IMAGE_SIZE_H;
	//�c��̐�
	const int COLUMN_NUM;
	const int ROW_NUM;
	const int EFFECT_NUM;
	//�G�t�F�N�g�������̑傫��
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

