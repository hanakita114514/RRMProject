#pragma once
#include "DataManager.h"

class Scene;
class Player;
class Collision;
class Block;


class GameMain
{
private:
	GameMain();
	GameMain(const GameMain&);
	GameMain& operator = (const GameMain&);

	Scene* _scene;
	Player* p1;

	DataManager _dataManager;

	SaveData _data;

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

	//すべてのデータの更新
	void DataUpdate(SaveData& data);

	//キャラクター情報の更新
	void CharacterDataUpdate(const CharacterData& data);

	//キャラクター情報のコピー
	//渡されたCharacterData構造体にキャラクター情報をコピーする
	void CharacterDataCopy(CharacterData & data);
};

