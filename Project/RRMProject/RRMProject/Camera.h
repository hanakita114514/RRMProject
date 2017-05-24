#pragma once

#include "Vector2.h"

//��ʈړ��A�h�炵�Ȃǂ��s���B
class Camera
{
private:
	Camera();
	Camera(const Camera&);
	Camera& operator = (const Camera&);

	Vector2 _offset;
public:
	~Camera();

	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
	
	void Init();
	void Update();
	void Quake();


	Vector2& GetOffset();

};

