#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

ObjectType
Object::GetObjType()
{
	return ObjectType::common;
}

void Object::Hit(Enemy* other)
{

}
void Object::Hit(Block* other)
{

}
void Object::Hit(Player* other)
{

}

void Object::Hit(Bullet* other)
{

}