#pragma once
#ifndef Matrix_h__
#define Matrix_h__

#include "Core/Core.h"
#include "Vector.h"

/*
KW_DECL_ALIGNED(16)
class Mat4f : public CMemAlign16
{
public:
	friend class GeomMath;
	friend class Quat;
	friend Mat4f Mul(const Mat4f& _left, const Mat4f& _right);
	friend Mat4f Inverse(const Mat4f& _val);

	Mat4f()
	{

	}

	Mat4f(float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44)
	{
		_data._11 = _11; _data._12 = _12; _data._13 = _13; _data._14 = _14;
		_data._21 = _21; _data._22 = _22; _data._23 = _23; _data._24 = _24;
		_data._31 = _31; _data._32 = _32; _data._33 = _33; _data._34 = _34;
		_data._41 = _41; _data._42 = _42; _data._43 = _43; _data._44 = _44;
	}

	Mat4f(const Vec4f& _r1, 
		const Vec4f& _r2, 
		const Vec4f& _r3,
		const Vec4f& _r4);

	inline Mat4f operator = (const Mat4f& _val) {  _data = _val._data; return *this; }

	inline Mat4f& operator *= (const Mat4f& _val)
	{
		this->_data = XMMatrixMultiply(this->_data, _val._data);
		return *this;
	}

	inline Mat4f operator * (const Mat4f& _val) const
	{
		return Mat4f(*this) *= _val;
	}

	inline XMFLOAT4X4 ToFloat4x4() const;
	inline void SetId();
	inline void SetRow(int _idx, const Vec4f& _v);
	inline Vec4f GetRow(int _idx) const;

	// Helper
	wstring Str();
	inline Vec4f Right() const { return GetRow(0); }
	inline Vec4f Up() const { return GetRow(1); } 
	inline Vec4f Forward() const { return GetRow(2); }
	
	const static Mat4f Id;

	static Mat4f CreateFromQuat(const Quat& _val)
	{
		return XMMatrixRotationQuaternion(_val._data);
	}

	static Mat4f Inverse(const Mat4f& _val)
	{
		XMVECTOR det;
		return XMMatrixInverse(&det, _val._data);
	}

	static Mat4f Translation(const Vec4f& _val)
	{
		return XMMatrixTranslationFromVector(_val._data);
	}

	static Mat4f Scale(float x, float y, float z)
	{
		return XMMatrixScaling(x, y, z);
	}

	void Transpose();
	void InverseOrtho();
private:
	XMMATRIX _data;
};

inline XMFLOAT4X4 Mat4f::ToFloat4x4() const
{
	XMFLOAT4X4 o;
	XMStoreFloat4x4(&o, _data);
	return o;
}

inline void Mat4f::SetId()
{
	_data = XMMatrixIdentity();
}

inline void Mat4f::SetRow(int _idx, const Vec4f& _v)
{
	_data(_idx, 0) = _v[0];
	_data(_idx, 1) = _v[1]; 
	_data(_idx, 2) = _v[2]; 
	_data(_idx, 3) = _v[3]; 
}

inline Vec4f Mat4f::GetRow( int _idx ) const
{
	return Vec4f(_data(_idx, 0), 
		_data(_idx, 1),
		_data(_idx, 2),
		_data(_idx, 3));
}

Mat4f Mul(const Mat4f& _left, const Mat4f& _right);
Mat4f Inverse( const Mat4f& _val );
*/

#endif // Matrix_h__