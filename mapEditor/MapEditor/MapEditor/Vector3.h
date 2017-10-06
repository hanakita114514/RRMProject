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

	//�R���X�g���N�^
	Vector3();
	Vector3(const float fx, const float fy, const float fz);
	Vector3(const Vector3& v);

	//���Z�q�̃I�[�o�[���[�h
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
	@brief ���g�̃x�N�g���̒�����Ԃ�
	@return �x�N�g���̒���
	*/
	float Length();

	/*
	@brief ���g�̃x�N�g���̒�����Ԃ�(sqrt�Ȃ�)
	@return �x�N�g���̒���
	*/
	float NotSqrtLength();

	/*
	@brief ���g�̃x�N�g���𐳋K�������l��Ԃ�
	@return ���K�������l
	*/
	Vector3 Normalized();

	/*
	@brief ���g�ƈ����̓��ς̒l��Ԃ�
	@param v �x�N�g��
	@return ���ς̒l
	*/
	float Dot(const Vector3& v);

	/*
	@brief ���g�ƈ����̊O�ς̒l��Ԃ�
	@param v �x�N�g��
	@return �O�ς̒l
	*/
	Vector3 Cross(const Vector3& v);

	/*
	@brief �����֌W��
	@param r �Ώ�
	@return true = �����@false = �����ł͂Ȃ�
	*/
	bool IsVertival(const Vector3& r);

	/*
	@brief ���s�֌W��
	@param r �Ώ�
	@return true = ���s�@false = ���s�ł͂Ȃ�
	*/
	bool IsParallel(const Vector3& r);

	/*
	@brief �݊p�֌W��
	@param r �Ώ�
	@return true = �݊p�@false = �s�p
	*/
	bool IsSharpAngle(const Vector3& r);

	/*
	@brief ���g�̒l��`�悷��
	@param posX x���W
	@param posY y���W
	@param col �F�@�f�t�H���g=��
	*/
	void Draw(const float posX,const float posY,const unsigned int col = 0xffffffff);

	/*
	@brief DxLib�̃x�N�^�[�l�ɕύX����
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
//@brief �x�N�g���̒�����Ԃ�
//@param v �x�N�g��
//@return �x�N�g���̒���
//*/
//static float Length(const Vector3& v)
//{
//	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
//}
//
///*
//@brief �x�N�g���𐳋K�������l��Ԃ�
//@param v �x�N�g��
//@return ���K�������l
//*/
//static Vector3 Normalized(const Vector3& v)
//{
//	float l = Length(v);
//	return Vector3(v.x / l, v.y / l, v.z / l);
//}

/*
@brief 2�̃x�N�g���̓��ς̒l��Ԃ�
@param v1 �x�N�g��1
@param v2 �x�N�g��2
@return ���ς̒l
*/
static float Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

/*
@brief 2�̃x�N�g���̓��ς̒l��Ԃ�
@param v1 �x�N�g��1
@param v2 �x�N�g��2
@return ���ς̒l
*/
static Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}


