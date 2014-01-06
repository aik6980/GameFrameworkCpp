#pragma once
#ifndef Vector_h__
#define Vector_h__

/*
#include "Core/Core.h"
#include "D3d11MathDefines.h"
#include "Tuple4.h"

class Vec4f : public Tuple4f
{
public:
	Vec4f() : Tuple4f(Origin) { }
	Vec4f(const Vec4f& rhs) : Tuple4f(rhs) { }
	Vec4f(float x, float y, float z, float w) : Tuple4f(x, y, z, w) { }

	inline Vec4f Point(float x, float y) { return Vec4f(x, y, 0.0f, 1.0f); }
	inline Vec4f Point(float x, float y, float z) { return Vec4f(x, y, z, 1.0f); }
	inline Vec4f Dir(float x, float y) { return Vec4f(x, y, 0.0f, 0.0f); }
	inline Vec4f Dir(float x, float y, float z) { return Vec4f(x, y, z, 0.0f); }

	inline Vec4f	XYZ()		{ return Vec4f( GetX(), GetY(), GetZ(), 0.0f ); };
	inline void		SetXYZ(const Vec4f& rhs) { SetX(rhs.GetX()); SetY(rhs.GetY()); SetZ(rhs.GetZ()); }

	inline Vec4f& operator += (const Vec4f& _val)
	{
		this->_data += _val._data;
		return *this;
	}

	inline Vec4f& operator -= (const Vec4f& _val)
	{
		this->_data -= _val._data;
		return *this;
	}

	inline Vec4f& operator *= (const Vec4f& _val)
	{
		this->_data *= _val._data;
		return *this;
	}

	inline const Vec4f operator + (const Vec4f& _val) { return Vec4f(*this) += _val; }
	inline const Vec4f operator - (const Vec4f& _val) const { return Vec4f(*this) -= _val; }
	inline const Vec4f operator * (const Vec4f& _val) { return Vec4f(*this) *= _val; }
	inline const Vec4f operator * (float _val)			
	{
		return Vec4f(this->GetX()*_val, this->GetY()*_val, this->GetZ()*_val, this->GetW()*_val);
	}
};
*/

#endif // Vector_h__