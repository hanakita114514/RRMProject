#pragma once

#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "EffectManager.h"

class Collision;

class GameScene : public Scene
{
private:
	Player _player;
	Collision* _col;
	std::vector<Block*> _colBlock;
	EffectManager _effectManager;
	
	Camera _camera;


	void EnemyColBlock();
	void PlayerColBlock();
	void PlayerColEnemy();
	void BulletColPlayer();
	void BulletColBlock();
	void BulletColEnemy();

	void ColProcess();

public:
	GameScene();
	~GameScene();

	bool Update();
};

