#pragma once
#include "Bullet.h"
class BezierBullet :
	public Bullet
{
public:
	BezierBullet(int handle, Vector2 entry);
	~BezierBullet();

private:
	int _freamCnt;
	float _t;		//�e�𔭎˂��Ă���̌o�ߎ���(0 < _t < 1)

	//�x�W�F�Ȑ��^���ɕK�v�ȎO�_
	//_ctlPoint�c����_�A_etyPoint�c�n�_�A_endPoint�c�I�_
	Vector2 _ctlPoint, _etyPoint, _endPoint;
	Vector2 _nextCtl;
	Vector2 _vec;

	//�ړ��ʌv�Z�Ɏg�����W
	Vector2 _nextPos;

	//�ЂƂ߂̐���_�̐ݒ�
	void ControlPointSet();

	//�ӂ��߂̐���_�̐ݒ�
	void NextControlPointSet();
	//�I�_�̐ݒ�
	void EndPointSet();
	//�x�W�F�Ȑ��^��
	void BezierCurve();
public:

	void Initialize(const Position& pos, Vector2 vec, ObjectType type);
	void Update();
	void Draw(const Vector2& offset);

	void Delete();
};

