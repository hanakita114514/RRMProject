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
	float _t;		//弾を発射してからの経過時間(0 < _t < 1)

	//ベジェ曲線運動に必要な三点
	//_ctlPoint…制御点、_etyPoint…始点、_endPoint…終点
	Vector2 _ctlPoint, _etyPoint, _endPoint;
	Vector2 _nextCtl;
	Vector2 _vec;

	//移動量計算に使う座標
	Vector2 _nextPos;

	//ひとつめの制御点の設定
	void ControlPointSet();

	//ふたつめの制御点の設定
	void NextControlPointSet();
	//終点の設定
	void EndPointSet();
	//ベジェ曲線運動
	void BezierCurve();
public:

	void Initialize(const Position& pos, Vector2 vec, ObjectType type);
	void Update();
	void Draw(const Vector2& offset);

	void Delete();
};

