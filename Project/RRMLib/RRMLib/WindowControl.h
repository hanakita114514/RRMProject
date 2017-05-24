#pragma once

#include <Windows.h>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//ウィンドウ関連の処理を担う
class WindowControl
{
private:
	HWND _hwnd;

	int _height;
	int _width;

	WindowControl();
	WindowControl(const WindowControl&);
	WindowControl& operator=(const WindowControl&);

public:
	~WindowControl();

	static WindowControl& Instance()
	{
		static WindowControl instance;

		return instance;
	}

	void Init();

	void SetGraphMode(int width, int height);

	HWND& WindowHandle();

	//ウィンドウの大きさを返す
	int WindowWidth();
	int WindowHeight();

	void ChangeFullScreenMode(bool fullScreen);
	
};

