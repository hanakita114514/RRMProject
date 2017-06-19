#include "BezierBullet.h"
#include "RRMLib.h"
#include "GameTime.h"

const float BULLET_SPEED = 5.0f;

const float REDUCE_LIFE = 1.0f;

BezierBullet::BezierBullet(int handle,Vector2 entry)
{
	_handle = handle;
	_id = BulletType::bezier;
	_etyPoint = entry;
}

BezierBullet::~BezierBullet()
{
}

void BezierBullet::Initialize(Vector2 vec, ObjectType type)
{
	_life = 100.0f;
	_objType = type;
	_isAlive = true;
	_t = 0;
	_vec = vec;
	_nextCtl = Vector2(980, 640);
	_nextCtl.x *= vec.x;
	_nextPos = Vector2(0, 0);

	EndPointSet();
	ControlPointSet();
}

void BezierBullet::Update()
{

	_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale();

	if (_life <= 0)
	{
		_isAlive = false;
	}

	BezierCurve();

	_circle.pos = _circle.pos - _vel * _vec.x;
}

void BezierBullet::Draw(const Vector2& offset)
{
	_circle.DrawGraph(_handle);
}

void BezierBullet::BezierCurve()
{
	_t += 0.01f;
	//時間経過による目標点の計算-----------------------------------------
	_nextPos.x = ((1 - _t) * (1 - _t) * (1 - _t) * _etyPoint.x) +
		(3 * (1 - _t) * (1 - _t) * _t * _ctlPoint.x) +
		(3 * (1 - _t) * _t * _t * _nextCtl.x)+
		(_t * _t * _t * _endPoint.x);

	_nextPos.y = ((1 - _t) * (1 - _t) * (1 - _t) * _etyPoint.y) +
		(3 * (1 - _t) * (1 - _t) * _t * _ctlPoint.y) +
		(3 * (1 - _t) * _t * _t * _nextCtl.y) +
		(_t * _t * _t * _endPoint.y);
	//-------------------------------------------------------------------

	//求めた結果と弾の現在座標からベクトルを計算、単位ベクトルに変換
	Vector2 normal = Normalize(_nextPos,_circle.pos);

	//単位ベクトルに弾のスピードをかける
	normal.x *= BULLET_SPEED * GameTime::Instance().GetTimeScale();
	normal.y *= BULLET_SPEED * GameTime::Instance().GetTimeScale();

	//求めた結果を移動量に代入
	_vel = normal;
}

void
BezierBullet::NextControlPointSet()
{

}

void
BezierBullet::ControlPointSet()
{
	if (_etyPoint.x > _endPoint.x && _endPoint.x < 0)
	{
		_ctlPoint = _etyPoint + _endPoint;
	}
	else if (_etyPoint.x > _endPoint.x && _endPoint.x > 0)
	{
		_ctlPoint = _etyPoint - _endPoint;
	}
	else
	{
		_ctlPoint = _endPoint - _etyPoint;
	}
	_ctlPoint.x +=_ctlPoint.x / 2;
}

void
BezierBullet::EndPointSet()
{
	if (_vec.x == -1)
	{
		_endPoint = _etyPoint;
		_endPoint.x = -1280;
	}
	else
	{
		_endPoint = _etyPoint;
		_endPoint.x = 1280;
	}
}


