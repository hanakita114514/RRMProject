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

	//���ׂẴf�[�^�̍X�V
	void DataUpdate(SaveData& data);

	//�L�����N�^�[���̍X�V
	void EqiupDataUpdata(const EquipmentInfometion& data);

	//�L�����N�^�[���̃R�s�[
	//�n���ꂽCharacterData�\���̂ɃL�����N�^�[�����R�s�[����
	void EqiupDataCopy(EquipmentInfometion& data);
};

