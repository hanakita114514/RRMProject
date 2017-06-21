#pragma once

//キャラにアーマーを持たせる
class Armor
{
private:
	float _endurance;
	float _enduranceMax;

	float _waitTime;

public:
	Armor(float endurance);
	~Armor();

	//自動回復させる場合毎回呼ぶ
	void AutomaticRecovery();
	//全回復
	void Recovery();
	//回復値を指定
	void Recovery(float recoval);
	//ダメージ
	void Damage(float damage);

	//アーマーが壊れたか？
	bool IsBroken();

};

