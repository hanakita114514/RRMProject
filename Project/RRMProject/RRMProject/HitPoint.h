#pragma once
class HitPoint
{
private:
	int _hp;
	int _maxHp;

public:
	HitPoint(int hp);	//HPを設定
	~HitPoint();

	void SetMaxHp(int hp);

	//回復
	void Recovery(int recval);
	//ダメージ
	void Damage(int damage);

	//HPが0であるか？
	bool IsDead();
	//HPが最大か？
	bool IsHpMax();

	int GetHitPoint();
	int GetMaxHP();
};

