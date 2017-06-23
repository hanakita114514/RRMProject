#pragma once
class HitPoint
{
private:
	float _hp;
	float _maxHp;

public:
	HitPoint(float hp);	//HPを設定
	~HitPoint();

	void SetMaxHp(float hp);

	//回復
	void Recovery(float recval);
	//ダメージ
	void Damage(float damage);

	//HPが0であるか？
	bool IsDead();
	//HPが最大か？
	bool IsHpMax();

	float GetHitPoint();
	float GetMaxHP();
};

