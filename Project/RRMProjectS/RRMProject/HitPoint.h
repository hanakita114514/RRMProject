#pragma once
class HitPoint
{
private:
	float _hp;
	float _maxHp;

public:
	HitPoint(float hp);	//HP��ݒ�
	~HitPoint();

	void SetMaxHp(float hp);

	//��
	void Recovery(float recval);
	//�_���[�W
	void Damage(float damage);

	//HP��0�ł��邩�H
	bool IsDead();
	//HP���ő傩�H
	bool IsHpMax();

	float GetHitPoint();
	float GetMaxHP();
};

