#pragma once

#include <vector>
#include "HitBox.h"

//プレイヤーの攻撃判定を作成するクラス
class PlayerHitBox
{
private:
	std::vector<HitBox> _hitboxes;

public:
	PlayerHitBox();
	~PlayerHitBox();

	void FirstAttack(float frame, const Rect& rc, const Vector2& dir);

	//当たり判定の描画(デバッグ用)
	void Draw();

	//攻撃判定を消す
	void Clear();

	std::vector<HitBox>& GetHitBoxes();
};

