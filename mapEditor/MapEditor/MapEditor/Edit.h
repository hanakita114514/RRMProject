#pragma once
#include "Vector3.h"
class Edit
{
private:
	Vector3 _size;
public:
	Edit();
	~Edit();

	void Init(float mapX, float mapY, float mapZ);

	void Draw();
};

