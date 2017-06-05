#pragma once
#include "Effect.h"
#include <vector>

class GeneralEffect : public Effect
{
private:
	//画像のサイズ
	const int IMAGE_SIZE_W;
	const int IMAGE_SIZE_H;
	//縦列の数
	const int COLUMN_NUM;
	const int ROW_NUM;
	const int EFFECT_NUM;
	//エフェクト一つ当たりの大きさ
	const int EFFECT_SIZE_W;
	const int EFFECT_SIZE_H;

	std::vector<Vector2> _animUV;

	//再生スピード 1 / speedの速さ
	float _speed;

	void (GeneralEffect::*_update)();
	void NormalUpdate();
	void LoopUpdate();

private:
	//アニメーションUV値を入れる
	//戻り値 アニメーションフレーム数が返る
	int AnimUV();

public:
	//rowDivNum 行分割数 columnDivNum 列分割数
	//speed  1 / speed の速さで再生する
	GeneralEffect(int handle, const Position& pos, 
		int imageSizeX, int imageSizeY, int rowDivNum, 
		int columnDivNum, float speed, const Vector2& size, bool isLoop);
	~GeneralEffect();

	void Update();
	//中央描画
	void Draw(const Vector2& offset);
};

