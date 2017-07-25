#pragma once

#include <vector>
#include "HitBox.h"

//�v���C���[�̍U��������쐬����N���X
class PlayerHitBox
{
private:
	std::vector<HitBox> _attackboxes; 
	std::vector<HitBox> _damageBox;

public:
	PlayerHitBox();
	~PlayerHitBox();

	void FirstAttack(float frame, const Rect& rc, const Vector2& dir);
	void SecondAttack(float frame, const Rect& rc, const Vector2& dir);
	void ThirdAttack(float frame, const Rect&rc, const Vector2& dir);

	void UpAttack(float frame, const Rect& rc, const Vector2& dir);

	void DamageBox(float frame, const Rect& rc, const Vector2& dir);
	//�����蔻��̕`��(�f�o�b�O�p)
	void Draw(int handle);

	//�U�����������
	void Clear();

	std::vector<HitBox>& GetAttackBoxes();
	std::vector<HitBox>& GetDamageBoxes();
};

