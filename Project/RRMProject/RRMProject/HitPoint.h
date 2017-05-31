#pragma once
class HitPoint
{
private:
	float _hp;
	float _maxHp;

public:
	HitPoint(int hp);	//HP��ݒ�
	~HitPoint();

	void SetMaxHp(int hp);

	//��
	void Recovery(int recval);
	//�_���[�W
	void Damage(int damage);

	//HP��0�ł��邩�H
	bool IsDead();
	//HP���ő傩�H
	bool IsHpMax();

	float GetHitPoint();
	float GetMaxHP();
};

