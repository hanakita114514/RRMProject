#pragma once

//��ʈړ��A�h�炵�Ȃǂ��s���B
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

