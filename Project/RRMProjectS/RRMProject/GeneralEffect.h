#pragma once
#include "Effect.h"
#include <vector>

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

	std::vector<Vector2> _animUV;

	//�Đ��X�s�[�h 1 / speed�̑���
	float _speed;

	void (GeneralEffect::*_update)();
	void NormalUpdate();
	void LoopUpdate();

private:
	//�A�j���[�V����UV�l������
	//�߂�l �A�j���[�V�����t���[�������Ԃ�
	int AnimUV();

public:
	//rowDivNum �s������ columnDivNum �񕪊���
	//speed  1 / speed �̑����ōĐ�����
	GeneralEffect(int handle, const Position& pos, 
		int imageSizeX, int imageSizeY, int rowDivNum, 
		int columnDivNum, float speed, const Vector2& size, bool isLoop);
	~GeneralEffect();

	void Update();
	//�����`��
	void Draw(const Vector2& offset);
};

