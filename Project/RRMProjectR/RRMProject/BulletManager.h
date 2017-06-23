#pragma once

#include "BulletFactory.h"
#include <vector>


//弾全体を管理するクラス
class BulletManager
{
private:
	std::vector<Bullet*> *bullet;
	BulletFactory _fac;

	BulletManager();
	BulletManager(const BulletManager&);
	BulletManager& operator = (const BulletManager&);
	
	//弾全体を管理する
	std::vector<Bullet*> _bulletList;

public:
	~BulletManager();

	static BulletManager& Instance()
	{
		static BulletManager instance;
		return instance;
	}

	void Update();
	void Draw(const Vector2& offset);

	Bullet* Create(const BulletType& bulletID, Vector2 vec, ObjectType type, Vector2 entry, Object* owner);

	void Delete();

	//指定したキャラの弾を消滅させる
	void Delete(Object* owner);

	std::vector<Bullet*>& GetBulletList();
};

