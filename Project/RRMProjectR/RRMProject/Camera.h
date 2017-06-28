#pragma once

#include "Vector2.h"
#include "Rect.h"

struct CameraRect
{
	Vector2 lpos;		//左上座標
	Vector2 rpos;		//右下座標
};

//画面移動、揺らしなどを行う。
class Camera
{
private:
	Vector2 _offset;
	Vector2 _quakeOffset;
	int _quakeFrame;

	Rect _rc;		//カメラの範囲
	Rect _mapRc;	//マップの大きさ

	const Position& _targetPos;	//カメラが追うキャラの位置

public:
	Camera(const Position& targetPos);
	~Camera();

	void Init();
	void Update();
	void Quake(const Vector2& power);

	//キャラの描画位置をずらす大きさを返す 結果を引く
	const Vector2& GetOffset();
	//マップの大きさを返す
	const Rect& GetMapSize();

	//カメラの見ている範囲を返す
	const CameraRect& GetCameraRect();
};

