#pragma once

#include "Scene.h"
#include "Player.h"
#include "Camera.h"

class Collision;

class GameScene : public Scene
{
private:
	bool _sceneChangeFlag;

	Player _player;
	Collision* _col;
	
	Camera _camera;

	void EnemyColBlock();
	void PlayerColBlock();
	void PlayerColEnemy();
	void BulletColPlayer();
	void BulletColBlock();
	void BulletColEnemy();

	void ColProcess();

	void StageClear();

public:
	GameScene();
	GameScene(LogoIdx state);
	~GameScene();

	bool Update();
};

