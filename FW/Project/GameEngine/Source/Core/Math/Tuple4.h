#pragma once
#ifndef Tuple4_h__
#define Tuple4_h__

#include "Core/Core.h"
#include "Math/Math.h"

template <class Type, int NumElems>
class TupleTpl
{
protected:
	Type _data[NumElems];
};

template <class T>
class Tuple4 : public TupleTpl<T, 4> , public CMemAlign16
{
public:
	Tuple4();
	Tuple4(const Tuple4<T>& rhs);
	Tuple4(T x, T y, T z, T w);

	inline Tuple4<T>& operator = (const Tuple4<T>& rhs);

	inline float& operator [] (int _idx)
	{
		return _data[_idx];
	}

	inline float operator [] (int _idx) const
	{
		return _data[_idx];
	}

	float	GetX() const	{ return (*this)[0]; }
	float	GetY() const	{ return (*this)[1]; }
	float	GetZ() const	{ return (*this)[2]; }
	float	GetW() const	{ return (*this)[3]; }
	void	SetX(float f)	{ (*this)[0] = f; }
	void	SetY(float f)	{ (*this)[1] = f; }
	void	SetZ(float f)	{ (*this)[2] = f; }
	void	SetW(float f)	{ (*this)[3] = f; }

	wstring Str();

	static int SizeInBytes() { return sizeof(Tuple4<T>); }
};

typedef KW_DECL_ALIGNED(16) Tuple4<float> Tuple4f;

#endif // Vector_h__