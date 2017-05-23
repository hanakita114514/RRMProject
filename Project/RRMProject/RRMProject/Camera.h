#pragma once

//画面移動、揺らしなどを行う。
class Camera
{
private:
	Camera();
	Camera(const Camera&);
	Camera& operator = (const Camera&);
public:
	~Camera();

	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
	
	void Init();
	void Update();

};

