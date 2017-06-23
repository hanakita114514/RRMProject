#pragma once

#include "Scene.h"
#include "Vector2.h"
#include "Arrow.h"
#include "Rect.h"
#include "DataManager.h"
#include <map>
class DInput;

//���S���i�[�p�\����
class MenuScene : public Scene
{
	typedef struct LOGO
	{
		int image;
		Rect rc;
		float freamCnt;
	}Logo;

	enum class WeaponType
	{
		tool,
		closeCombat,
		max
	};

	const float LogoHeight = 64;
	const float LogoWidth = 52;

private:
	int _titleHandle;
	int _stageId;					//�X�e�[�WID
	int _logoIdx;					//Logo�\���̔z��̓Y����
	int _toolIdx;					//��ѓ���z��̓Y����
	int _weaponIdx;					//����z��̓Y����
	int _bg;						//�w�i�̉摜�n���h��
	float _freamCnt;

	Arrow _arrow;				//���
	Logo _logo[(int)(LogoIdx::logoMax)];			//���S�̉摜�n���h��
	DInput* _dinput;
	Vector2 _logoDefaultPos[(int)(LogoIdx::logoMax)];
	Vector2 _velocity;								//���̈ړ���
	EquipmentInfometion _data;

	bool prevRight, prevLeft,prevUp,prevDown;	//�O�t���[���̃X�e�B�b�N���
	bool right, left,up,down;			//���t���[���̃X�e�B�b�N���

	void (MenuScene::*_update)();
	void TitleUpdate();
	void MenuUpdate();
	void StageSelect();
	void GameStart();
	void Configuration();

	void Draw();

	void LogoMove();

	void UpMove();
	void DownMove();
	int RightMove(int& idx, int idxMax);
	int LeftMove(int idx, int idxMax);

	void TypeOfWeapons();

	void WeaponSelect();
	void ToolSelect();

	bool Exit();

	Vector2 ImageShaker(Rect& rect);

public:

	MenuScene();
	~MenuScene();

	bool Update();

	bool IsStickRight();
	bool IsStickLeft();
	bool IsStickUp();
	bool IsStickDown();

};