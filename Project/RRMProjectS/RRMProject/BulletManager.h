#pragma once

#include "BulletFactory.h"
#include <vector>


//�e�S�̂��Ǘ�����N���X
class BulletManager
{
private:
	std::vector<Bullet*> *bullet;
	BulletFactory _fac;

	BulletManager();
	BulletManager(const BulletManager&);
	BulletManager& operator = (const BulletManager&);
	
	//�e�S�̂��Ǘ�����
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

	//�w�肵���L�����̒e�����ł�����
	void Delete(Object* owner);

	std::vector<Bullet*>& GetBulletList();
};

