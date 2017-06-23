#pragma once

#include <vector>
#include "HitBox.h"

//�v���C���[�̍U��������쐬����N���X
class PlayerHitBox
{
private:
	std::vector<HitBox> _hitboxes;

public:
	PlayerHitBox();
	~PlayerHitBox();

	void FirstAttack(float frame, const Rect& rc, const Vector2& dir);

	//�����蔻��̕`��(�f�o�b�O�p)
	void Draw();

	//�U�����������
	void Clear();

	std::vector<HitBox>& GetHitBoxes();
};

