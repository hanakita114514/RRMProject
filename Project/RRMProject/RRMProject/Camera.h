#pragma once

#include "Vector2.h"

//‰æ–ÊˆÚ“®A—h‚ç‚µ‚È‚Ç‚ğs‚¤B
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

