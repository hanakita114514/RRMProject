#pragma once
#include "Rect.h"

class MenuInformation
{
private:
	int _handle;
	float _extendX;						//�����̊g��l
	float _extendY;						//�c���̊g��l
	int _ExRate;
	int _alpha;

	Vector2 _extendPos[2];

	bool _isEnlargement;				//�g�咆
	bool _isReduction;					//�k����
	bool _isWait;						//�ҋ@��

	void (MenuInformation::*_update)();
	void Enlargement();
	void Reduction();
	void Wait();

public:
	MenuInformation();
	~MenuInformation();
	void Init();

	void Update();

	void Draw();

	void Enlargement(int extendRate, int alpha);
	void Reduction(int extendRate);

	bool IsEnlargement() { return _isEnlargement; }
	bool IsReduction() { return _isReduction; }
	bool IsWait() { return _isWait; }
};

