#pragma once

#include "HitBox.h"
#include <vector>
#include "Rect.h"

class EnemyHitBox
{
protected:
	std::vector<Rect> _searchRect;
	std::vector<Rect> _footRect;
	std::vector<HitBox> _attackBox;

public:
	EnemyHitBox();
	~EnemyHitBox();


	virtual void Search(float frame, const Rect& rc, const Vector2& dir);
	virtual void Foot(float frame, const Rect& rc, const Vector2& dir);
	virtual void Attack(float frame, const Rect& rc, const Vector2& dir);

	void Clear();
	void SearchClear();

	std::vector<Rect>& GetSearchRects();
	std::vector<Rect>& GetFootRects();
	std::vector<HitBox>& GetAttackBoxes();
};

