#include "MultihitProtect.h"



MultihitProtect::MultihitProtect()
{
}


MultihitProtect::~MultihitProtect()
{
}

void 
MultihitProtect::Hit(Object* other)
{
	_hitMap[other] = true;
}

void 
MultihitProtect::Clear()
{
	_hitMap.clear();
}