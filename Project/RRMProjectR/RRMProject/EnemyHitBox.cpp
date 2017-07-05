#include "EnemyHitBox.h"



EnemyHitBox::EnemyHitBox()
{
}


EnemyHitBox::~EnemyHitBox()
{
}

std::vector<Rect>& 
EnemyHitBox::GetSearchRects()
{
	return _searchRect;
}

std::vector<Rect>& 
EnemyHitBox::GetFootRects()
{
	return _footRect;
}

std::vector<HitBox>& 
EnemyHitBox::GetAttackBoxes()
{
	return _attackBox;
}

void 
EnemyHitBox::Search(float frame, const Rect& rc, const Vector2& dir)
{

}

void 
EnemyHitBox::Foot(float frame, const Rect& rc, const Vector2& dir)
{

}
void 
EnemyHitBox::Attack(float frame, const Rect& rc, const Vector2& dir)
{

}

void 
EnemyHitBox::Clear()
{
	_attackBox.clear();
	_footRect.clear();
	_searchRect.clear();
}

void 
EnemyHitBox::SearchClear()
{
	_searchRect.clear();
}