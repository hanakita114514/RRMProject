#pragma once

#include "Vector2.h"
#include "Rect.h"

//��ʈړ��A�h�炵�Ȃǂ��s���B
class Camera
{
private:
	Vector2 _offset;
	Vector2 _quakeOffset;
	int _quakeFrame;

	Rect _rc;
	Rect _mapRc;

	const Position& _targetPos;

public:
	Camera(const Position& targetPos);
	~Camera();

	void Init();
	void Update();
	void Quake(const Vector2& power);

	const Vector2& GetOffset();
	//�}�b�v�̑傫����Ԃ�
	const Rect& GetMapSize();

};

