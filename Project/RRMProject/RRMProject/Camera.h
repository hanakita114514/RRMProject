#pragma once

//‰æ–ÊˆÚ“®A—h‚ç‚µ‚È‚Ç‚ğs‚¤B
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

