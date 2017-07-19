#pragma once

#include "Vector2.h"
#include "CircleObj.h"
#include "GameTime.h"

const int LIFE_DEF = 20;

//弾の画像サイズは24*24
//弾自体のサイズは24*24にしてあります
const float BULLET_RADIUS = 24 / 2;		//半径

enum class BulletType
{
	none,
	normal,					//通常弾
	homing,					//ホーミング弾
	sinBullet,
	lazer,
	bezier,					//ベジェ曲線弾
	deffusion,				//拡散
	circleBullet,			//放射状に飛ぶ
	rainBullet,				//雨のように落ちる
	//ここに追加

	num,
};

class Bullet : public CircleObj
{
protected:
	BulletType _id;		//弾の種類
	Vector2 _vel;	//弾の速度
	bool _isAlive;	//生きているか？
	ObjectType _objType;	//敵、プレイヤーの区別のタイプ
	float _life;				//弾の寿命
	float _pow;					//攻撃力

	Object* _owner;

	bool _isHitGround;
protected:
	enum class BulletState
	{
		move,
		stop
	};

	BulletState _bs;

public:
	Bullet();
	virtual ~Bullet();

	GameTime& _gameTime;

	BulletType GetID();						//IDの取得
	bool IsAlive();						//生きているか？
	virtual void Initialize(const Position& pos, Vector2 vec, ObjectType type);				//初期化
	virtual void Update() = 0;						//更新
	virtual void Draw(const Vector2& offset) = 0;						//描画
	virtual void Finalize();
	ObjectType GetObjType();

	//弾を使用したキャラのポインタを返す
	Object* GetOwner();
	void SetOwner(Object* obj);

	void Destory() { _isAlive = false; }
	void HitGround();

	void LifeDecrease();	//ライフを減らす

	void Hit(Player* otheer);
	void Hit(Enemy* other);
	void Hit(Block* other);
	void Hit(Bullet* other);

	Vector2 GetVel() { return _vel; }
	float GetPower() { return _pow; }

	void Stop() { _bs = BulletState::stop; }
	void Move() { _bs = BulletState::move; }
};


