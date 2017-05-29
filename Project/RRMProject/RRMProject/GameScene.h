#pragma once

#include "Scene.h"
#include "Player.h"
#include "Camera.h"

class Collision;

class GameScene : public Scene
{
private:
	Player _player;
	Collision* _col;
	std::vector<Block*> _colBlock;
	
	Camera _camera;


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

