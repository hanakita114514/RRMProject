#pragma once

#include "Scene.h"
#include "Player.h"

class Collision;

class GameScene : public Scene
{
private:
	Player _player;
	Collision* _col;
	std::vector<Block*> _colBlock;


	void EnemyColBlock();
	void PlayerColBlock();
	void PlayerColEnemy();
	void BulletColPlayer();
	void BulletColBlock();
	void CreateColBox();
	void BulletColEnemy();
	void ColProcess();

public:
	GameScene();
	~GameScene();

	bool Update();
};

