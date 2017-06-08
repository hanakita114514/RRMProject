#pragma once

#include "Scene.h"
#include "Vector2.h"
#include "Arrow.h"

class DInput;

class MenuScene : public Scene
{
private:
	int _titleHandle;
	int _gameStartLogo;			//���S�̉摜�n���h��
	int _stageId;				//�X�e�[�WID
	DInput* _dinput;

	Position _logoPosition;		//���S�̈ʒu
	Arrow _arrow;				//���

	bool prevRight, prevLeft;	//�O�t���[���̃X�e�B�b�N���
	bool right, left;			//���t���[���̃X�e�B�b�N���
	bool _fadeOutIn;			//�t�F�[�h�A�E�g���m�p�t���O

	void (MenuScene::*_update)();

	void TitleUpdate();
	void MenuUpdate();

	void GameStart();
	void StageSelect();
public:
	MenuScene();
	~MenuScene();

	bool Update();

};

