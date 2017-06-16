#include "WindowControl.h"
#include <D3D11.h>
#include "DeviceDx11.h"

WindowControl::WindowControl()
{
	_height = WINDOW_HEIGHT;
	_width = WINDOW_WIDTH;
}


WindowControl::~WindowControl()
{
}

//ウィンドウのコールバック関数
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wpal, LPARAM lpal)
{
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wpal, lpal);
}


void
WindowControl::Init()
{
	//ウィンドウクラスの作成と登録
	WNDCLASS w = WNDCLASS();
	w.lpfnWndProc = (WNDPROC)WindowProcedure;
	w.lpszClassName = "ClassName";
	w.hInstance = GetModuleHandle(0);
	RegisterClass(&w);

	//ウィンドウサイズの設定
	RECT wrc = { 0,0,_width,_height };
	::AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの生成
	_hwnd = CreateWindow(w.lpszClassName,
		"DirectX",
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr);
}

void
WindowControl::SetGraphMode(int width, int height)
{
	_width = width;
	_height = height;
	Init();
}

HWND&
WindowControl::WindowHandle()
{
	return _hwnd;
}


int 
WindowControl::WindowWidth()
{
	return _width;
}

int 
WindowControl::WindowHeight()
{
	return _height;
}

void 
WindowControl::ChangeFullScreenMode(bool fullScreen)
{
	DeviceDx11::Instance().SwapChain()->SetFullscreenState(fullScreen, nullptr);
}
