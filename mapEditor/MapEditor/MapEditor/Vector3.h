#pragma once
struct Vector3;
namespace DxLib
{
	struct tagVECTOR;
	typedef tagVECTOR VECTOR;
	VECTOR GetVector3ToVECTOR(const Vector3& v);
}
using namespace DxLib;

struct Vector3
{
	float x, y, z;

	//コンストラクタ
	Vector3();
	Vector3(const float fx, const float fy, const float fz);
	Vector3(const Vector3& v);

	//演算子のオーバーロード
	void operator = (const float fv);
	void operator += (const float fv);
	void operator -= (const float fv);
	void operator *= (const float fv);
	void operator /= (const float fv);
	void operator += (const Vector3& v);
	void operator -= (const Vector3& v);
	void operator *= (const Vector3& v);
	void operator /= (const Vector3& v);

	/*
	@brief 自身のベクトルの長さを返す
	@return ベクトルの長さ
	*/
	float Length();

	/*
	@brief 自身のベクトルの長さを返す(sqrtなし)
	@return ベクトルの長さ
	*/
	float NotSqrtLength();

	/*
	@brief 自身のベクトルを正規化した値を返す
	@return 正規化した値
	*/
	Vector3 Normalized();

	/*
	@brief 自身と引数の内積の値を返す
	@param v ベクトル
	@return 内積の値
	*/
	float Dot(const Vector3& v);

	/*
	@brief 自身と引数の外積の値を返す
	@param v ベクトル
	@return 外積の値
	*/
	Vector3 Cross(const Vector3& v);

	/*
	@brief 垂直関係か
	@param r 対象
	@return true = 垂直　false = 垂直ではない
	*/
	bool IsVertival(const Vector3& r);

	/*
	@brief 平行関係か
	@param r 対象
	@return true = 平行　false = 平行ではない
	*/
	bool IsParallel(const Vector3& r);

	/*
	@brief 鈍角関係か
	@param r 対象
	@return true = 鈍角　false = 鋭角
	*/
	bool IsSharpAngle(const Vector3& r);

	/*
	@brief 自身の値を描画する
	@param posX x座標
	@param posY y座標
	@param col 色　デフォルト=白
	*/
	void Draw(const float posX,const float posY,const unsigned int col = 0xffffffff);

	/*
	@brief DxLibのベクター値に変更する
	@return DxLib::VECTOR
	*/
	VECTOR GetVECTOR();
};

inline Vector3 operator + (const Vector3& v1, const Vector3& v2)
{
	Vector3 ret = {};
	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return ret;
}
inline Vector3 operator - (const Vector3& v1, const Vector3& v2)
{
	Vector3 ret = {};
	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return ret;
}
inline Vector3 operator * (const Vector3& v1, const Vector3& v2)
{
	Vector3 ret = {};
	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	ret.z = v1.z * v2.z;
	return ret;
}
inline Vector3 operator / (const Vector3& v1, const Vector3& v2)
{
	Vector3 ret = {};
	if (v2.x != 0)
	{
		ret.x = v1.x / v2.x;
	}
	if (v2.y != 0)
	{
		ret.y = v1.y / v2.y;
	}
	if (v2.z != 0)
	{
		ret.z = v1.z / v2.z;
	}
	return ret;
}

inline Vector3 operator + (const Vector3& v1, const float fv)
{
	Vector3 ret = {};
	ret.x = v1.x + fv;
	ret.y = v1.y + fv;
	ret.z = v1.z + fv;
	return ret;
}
inline Vector3 operator - (const Vector3& v1, const float fv)
{
	Vector3 ret = {};
	ret.x = v1.x - fv;
	ret.y = v1.y - fv;
	ret.z = v1.z - fv;
	return ret;
}
inline Vector3 operator * (const Vector3& v1, const float fv)
{
	Vector3 ret = {};
	ret.x = v1.x * fv;
	ret.y = v1.y * fv;
	ret.z = v1.z * fv;
	return ret;
}
inline Vector3 operator / (const Vector3& v1, const float fv)
{
	Vector3 ret = {};
	if (fv != 0.0f)
	{
		ret.x = v1.x / fv;
		ret.y = v1.y / fv;
		ret.z = v1.z / fv;
	}
	return ret;
}

///*
//@brief ベクトルの長さを返す
//@param v ベクトル
//@return ベクトルの長さ
//*/
//static float Length(const Vector3& v)
//{
//	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
//}
//
///*
//@brief ベクトルを正規化した値を返す
//@param v ベクトル
//@return 正規化した値
//*/
//static Vector3 Normalized(const Vector3& v)
//{
//	float l = Length(v);
//	return Vector3(v.x / l, v.y / l, v.z / l);
//}

/*
@brief 2つのベクトルの内積の値を返す
@param v1 ベクトル1
@param v2 ベクトル2
@return 内積の値
*/
static float Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

/*
@brief 2つのベクトルの内積の値を返す
@param v1 ベクトル1
@param v2 ベクトル2
@return 内積の値
*/
static Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}


