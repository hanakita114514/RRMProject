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

	//���ׂẴf�[�^�̍X�V
	void DataUpdate(SaveData& data);

	//�L�����N�^�[���̍X�V
	void CharacterDataUpdate(const CharacterData& data);

	//�L�����N�^�[���̃R�s�[
	//�n���ꂽCharacterData�\���̂ɃL�����N�^�[�����R�s�[����
	void CharacterDataCopy(CharacterData & data);
};

