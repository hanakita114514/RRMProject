#pragma once

struct Vector2
{
	float x, y;

	//�R���X�g���N�^
	Vector2();
	Vector2(const float fx, const float fy);
	Vector2(const Vector2& v);

	//���Z�q�̃I�[�o�[���[�h
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
	@brief ���g�̃x�N�g���̒�����Ԃ�
	@return �x�N�g���̒���
	*/
	float Length();

	/*
	@brief ���g�̃x�N�g���𐳋K�������l��Ԃ�
	@return ���K�������l
	*/
	Vector2 Normalized();

	/*
	@brief ���g�ƈ����̓��ς̒l��Ԃ�
	@param v �x�N�g��
	@return ���ς̒l
	*/
	float Dot(const Vector2& v);

	/*
	@brief ���g�ƈ����̊O�ς̒l��Ԃ�
	@param v �x�N�g��
	@return �O�ς̒l
	*/
	float Cross(const Vector2& v);

	/*
	@brief ���g�̒l��`�悷��
	@param posX x���W
	@param posY y���W
	@param col �F�@�f�t�H���g=��
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
//@brief �x�N�g���̒�����Ԃ�
//@param v �x�N�g��
//@return �x�N�g���̒���
//*/
//static float Length(const Vector2& v);
//
///*
//@brief �x�N�g���𐳋K�������l��Ԃ�
//@param v �x�N�g��
//@return ���K�������l
//*/
//static Vector2 Normalized(const Vector2& v);

/*
@brief 2�̃x�N�g���̓��ς̒l��Ԃ�
@param v1 �x�N�g��1
@param v2 �x�N�g��2
@return ���ς̒l
*/
static float Dot(const Vector2& v1, const Vector2& v2);

/*
@brief 2�̃x�N�g���̓��ς̒l��Ԃ�
@param v1 �x�N�g��1
@param v2 �x�N�g��2
@return ���ς̒l
*/
static float Cross(const Vector2& v1, const Vector2& v2);

