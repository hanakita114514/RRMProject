#pragma once

#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "StatusUI.h"
#include "PlayerHP.h"
#include "KeyConfig.h"

class Collision;

class GameScene : public Scene
{
private:
	bool _sceneChangeFlag;

	Player _player;
	PlayerHP _playerHP;
	Collision* _col;
	StatusUI _statusUI;
	
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
	GameScene(LogoIdx state, KeyData& keyData);
	~GameScene();

	bool Update();
};

