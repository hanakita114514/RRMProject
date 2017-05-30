#pragma once

#include "Vector2.h"
#include "CircleObj.h"

const int LIFE_DEF = 20;
//弾の画像サイズは24*24
//弾自体のサイズは22*22にしてあります
const float BULLET_RADIUS = 22 / 2;		//半径

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

	Object* _owner;

public:
	Bullet();
	virtual ~Bullet();

	BulletType GetID();						//IDの取得
	bool IsAlive();						//生きているか？
	virtual void Initialize(Vector2 vec, ObjectType type);				//初期化
	virtual void Update() = 0;						//更新
	virtual void Draw(const Vector2& offset) = 0;						//描画
	ObjectType GetObjType();

	//弾を使用したキャラのポインタを返す
	Object* GetOwner();
	void SetOwner(Object* obj);

	inline void Destory() { _isAlive = false; }

	void Hit(Player* otheer);
	void Hit(Enemy* other);
	void Hit(Block* other);

	Vector2 GetVel() { return _vel; }
};


