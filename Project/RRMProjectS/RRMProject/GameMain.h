#pragma once
#include <vector>

class Scene;
class Player;
class Collision;
class Rect;
class Block;

class GameMain
{
private:
	GameMain();
	GameMain(const GameMain&);
	GameMain& operator = (const GameMain&);

	Scene* _scene;
	Player* p1;
	//BulletManager* _bullet;
	//MapManager* _map;
	//EnemyManager* _enemy;
	Collision* _col;

	std::vector<Block*> _colBlock;

	void PlayerColBlock(Player *p);
	void EnemyColBlock();
	void PlayerColEnemy(Player *p);
	void BulletColPlayer(Player *p);
	void BulletColBlock();
	void BulletColEnemy();

	void CreateColBox();

	void ColProcess(Player* p);


public:
	~GameMain();

	static GameMain& Instance()
	{
		static GameMain instance;
		return instance;
	}

	bool Init();
	void GameLoop();
	void Terminate();

	void ChangeScene(Scene* scene);
	//BulletManager* GetBulletMng()		{return _bullet;}
	//MapManager* GetMap()				{ return _map; }
	//EnemyManager* GetEnemy() { return _enemy; }

};

