#pragma once
#include "Block.h"
#include <vector>

class MapRendar;
class BackgroundRendar;
class EnemyFactory;
class Enemy;

class MapManager
{
private:
	MapRendar* _map;
	BackgroundRendar* _bg;
	EnemyFactory* _fac;
	Enemy* newEnemy;

	bool _mapErr;				//�}�b�v�ǂݍ��݃G���[�p�t���O
	bool _bgErr;				//�w�i�ǂݍ��݃G���[�p�t���O
	bool createFlug;			//�f�o�b�O�p�G�����t���O
	std::vector<Block> _list;

	MapManager();
	MapManager(const MapManager&);
	MapManager& operator = (const MapManager&);


public:
	~MapManager();

	static MapManager& Instance()
	{
		static MapManager instance;
		return instance;
	}

	bool Initialize();
	void Draw();
	void Update();
	void Finalize();

	EnemyFactory* GetEnemyFact() { return _fac; }
	std::vector<Block>& GetList() { return _list; }
	MapRendar* GetMap() { return _map; }
};

