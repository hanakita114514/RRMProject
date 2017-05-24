#pragma once
#include <vector>

class Scene;
class BulletManeger;
class MapManeger;
class EnemyManager;
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
	BulletManeger* _bullet;
	MapManeger* _map;
	EnemyManager* _enemy;
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
	BulletManeger* GetBulletMng()		{return _bullet;}
	MapManeger* GetMap()				{ return _map; }
	EnemyManager* GetEnemy() { return _enemy; }

};

