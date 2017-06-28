#pragma once

#include "Vector2.h"
#include "Rect.h"

struct CameraRect
{
	Vector2 lpos;		//������W
	Vector2 rpos;		//�E�����W
};

//��ʈړ��A�h�炵�Ȃǂ��s���B
class Camera
{
private:
	Vector2 _offset;
	Vector2 _quakeOffset;
	int _quakeFrame;

	Rect _rc;		//�J�����͈̔�
	Rect _mapRc;	//�}�b�v�̑傫��

	const Position& _targetPos;	//�J�������ǂ��L�����̈ʒu

public:
	Camera(const Position& targetPos);
	~Camera();

	void Init();
	void Update();
	void Quake(const Vector2& power);

	//�L�����̕`��ʒu�����炷�傫����Ԃ� ���ʂ�����
	const Vector2& GetOffset();
	//�}�b�v�̑傫����Ԃ�
	const Rect& GetMapSize();

	//�J�����̌��Ă���͈͂�Ԃ�
	const CameraRect& GetCameraRect();
};

