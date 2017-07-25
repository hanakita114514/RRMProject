#pragma once

#include "Vector2.h"
#include <map>
#include "Rect.h"

enum class PlayerState : unsigned int
{
	none,

	neutral,
	walk,
	attack,
	shoot,
	avoidance,
	invincible,
	damage,
	jump,
	die,
};

class PlayerDraw
{
private:
	typedef void (PlayerDraw::*_func)(const Vector2& pos);

	std::map<PlayerState, int> _handleMap;
	int _handle;

	int _frame;

	std::map<PlayerState, _func> _draw;
	void NeutralDraw(const Vector2& pos);
	void WalkDraw(const Vector2& pos);
	void AvoidanceDraw(const Vector2& pos);
	void AttackDraw(const Vector2& pos);
	void InvincibleDraw(const Vector2& pos);
	void DamageDraw(const Vector2& pos);
	void DieDraw(const Vector2& pos);
	void JumpDraw(const Vector2& pos);
	void ShootDraw(const Vector2& pos);

	const Rect& _playerRc;

	Vector2 _uv;
	const Vector2& _dir;

public:
	PlayerDraw(const Rect& rc, const Vector2& dir);
	~PlayerDraw();

	void Draw(const Vector2& pos, const PlayerState& state);
};

