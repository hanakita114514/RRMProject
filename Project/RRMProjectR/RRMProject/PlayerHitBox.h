#pragma once

#include <vector>
#include "HitBox.h"

//プレイヤーの攻撃判定を作成するクラス
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
	//当たり判定の描画(デバッグ用)
	void Draw(int handle);

	//攻撃判定を消す
	void Clear();

	std::vector<HitBox>& GetAttackBoxes();
	std::vector<HitBox>& GetDamageBoxes();
};

