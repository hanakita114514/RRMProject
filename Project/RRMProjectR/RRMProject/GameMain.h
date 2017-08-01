#pragma once
#include "DataManager.h"
#include "KeyConfig.h"

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

	Player* p1;


	SaveData _data;
	KeyConfig _keyConfig;

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

	//すべてのデータの更新
	void DataUpdate(SaveData& data);

	//キャラクター情報の更新
	void EqiupDataUpdata(const EquipmentInfometion& data);

	//キャラクター情報のコピー
	//渡されたCharacterData構造体にキャラクター情報をコピーする
	void EqiupDataCopy(EquipmentInfometion& data);
};

