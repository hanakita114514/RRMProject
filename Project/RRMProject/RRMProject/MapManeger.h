#pragma once
#include "Block.h"
#include <vector>

class MapRendar;
class BackgroundRendar;
class EnemyFactory;
class EnemyManager;
class Enemy;

class MapManeger
{
private:
	MapRendar* _map;
	BackgroundRendar* _bg;
	EnemyFactory* _fac;
	EnemyManager* _enemy;
	Enemy* newEnemy;

	bool _mapErr;				//�}�b�v�ǂݍ��݃G���[�p�t���O
	bool _bgErr;				//�w�i�ǂݍ��݃G���[�p�t���O
	bool createFlug;			//�f�o�b�O�p�G�����t���O
	std::vector<Block> _list;
public:
	MapManeger();
	~MapManeger();

	bool Initialize();
	void Draw();
	void Update();
	void Finalize();

	EnemyFactory* GetEnemyFact() { return _fac; }
	std::vector<Block> GetList() { return _list; }
	MapRendar* GetMap() { return _map; }
};

