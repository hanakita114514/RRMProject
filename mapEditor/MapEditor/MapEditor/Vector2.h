#pragma once

struct Vector2
{
	float x, y;

	//コンストラクタ
	Vector2();
	Vector2(const float fx, const float fy);
	Vector2(const Vector2& v);

	//演算子のオーバーロード
	void operator = (const float fv);
	void operator += (const float fv);
	void operator -= (const float fv);
	void operator *= (const float fv);
	void operator /= (const float fv);
	void operator += (const Vector2& v);
	void operator -= (const Vector2& v);
	void operator *= (const Vector2& v);
	void operator /= (const Vector2& v);

	/*
	@brief 自身のベクトルの長さを返す
	@return ベクトルの長さ
	*/
	float Length();

	/*
	@brief 自身のベクトルを正規化した値を返す
	@return 正規化した値
	*/
	Vector2 Normalized();

	/*
	@brief 自身と引数の内積の値を返す
	@param v ベクトル
	@return 内積の値
	*/
	float Dot(const Vector2& v);

	/*
	@brief 自身と引数の外積の値を返す
	@param v ベクトル
	@return 外積の値
	*/
	float Cross(const Vector2& v);

	/*
	@brief 自身の値を描画する
	@param posX x座標
	@param posY y座標
	@param col 色　デフォルト=白
	*/
	void Draw(const float posX, const float posY, const unsigned int col = 0xffffffff);
};

inline Vector2 operator + (const Vector2& v1, const Vector2& v2)
{
	Vector2 ret = {};
	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	return ret;
}
inline Vector2 operator - (const Vector2& v1, const Vector2& v2)
{
	Vector2 ret = {};
	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	return ret;
}
inline Vector2 operator * (const Vector2& v1, const Vector2& v2)
{
	Vector2 ret = {};
	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	return ret;
}
inline Vector2 operator / (const Vector2& v1, const Vector2& v2)
{
	Vector2 ret = {};
	if (v2.x != 0)
	{
		ret.x = v1.x / v2.x;
	}
	if (v2.y != 0)
	{
		ret.y = v1.y / v2.y;
	}
	return ret;
}

inline Vector2 operator + (const Vector2& v1, const float fv)
{
	Vector2 ret = {};
	ret.x = v1.x + fv;
	ret.y = v1.y + fv;
	return ret;
}
inline Vector2 operator - (const Vector2& v1, const float fv)
{
	Vector2 ret = {};
	ret.x = v1.x - fv;
	ret.y = v1.y - fv;
	return ret;
}
inline Vector2 operator * (const Vector2& v1, const float fv)
{
	Vector2 ret = {};
	ret.x = v1.x * fv;
	ret.y = v1.y * fv;
	return ret;
}
inline Vector2 operator / (const Vector2& v1, const float fv)
{
	Vector2 ret = {};
	if (fv != 0.0f)
	{
		ret.x = v1.x / fv;
		ret.y = v1.y / fv;
	}
	return ret;
}

///*
//@brief ベクトルの長さを返す
//@param v ベクトル
//@return ベクトルの長さ
//*/
//static float Length(const Vector2& v);
//
///*
//@brief ベクトルを正規化した値を返す
//@param v ベクトル
//@return 正規化した値
//*/
//static Vector2 Normalized(const Vector2& v);

/*
@brief 2つのベクトルの内積の値を返す
@param v1 ベクトル1
@param v2 ベクトル2
@return 内積の値
*/
static float Dot(const Vector2& v1, const Vector2& v2);

/*
@brief 2つのベクトルの内積の値を返す
@param v1 ベクトル1
@param v2 ベクトル2
@return 内積の値
*/
static float Cross(const Vector2& v1, const Vector2& v2);

