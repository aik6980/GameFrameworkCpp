#include "stdafx.h"
/*
#include "Matrix.h"

const Mat4f Mat4f::Id( 1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f );

Mat4f::Mat4f( const Vec4f& _r1, const Vec4f& _r2, const Vec4f& _r3, const Vec4f& _r4 )
{
	SetRow(0, _r1);
	SetRow(1, _r2);
	SetRow(2, _r3);
	SetRow(3, _r4);
}

std::wstring Mat4f::Str()
{
	return (boost::wformat(L"matrix print start \n"
		L"%4.4f %4.4f %4.4f %4.4f \n"
		L"%4.4f %4.4f %4.4f %4.4f \n"
		L"%4.4f %4.4f %4.4f %4.4f \n"
		L"%4.4f %4.4f %4.4f %4.4f \n"
		L"matrix print end") % 
		_data._11 % _data._12 % _data._13 % _data._14 %
		_data._21 % _data._22 % _data._23 % _data._24 %
		_data._31 % _data._32 % _data._33 % _data._34 %
		_data._41 % _data._42 % _data._43 % _data._44 ).str();
}

Mat4f Mul(const Mat4f& _left, const Mat4f& _right)
{
	Mat4f o;
	o._data = XMMatrixMultiply(_left._data, _right._data);
	return o;
}

Mat4f Inverse( const Mat4f& _val )
{
	Mat4f o;
	XMVECTOR oDet;
	o._data = XMMatrixInverse(&oDet, _val._data);
	return o;
}

void Mat4f::Transpose()
{
	_data = XMMatrixTranspose(_data);
}

void Mat4f::InverseOrtho()
{
	Transpose();
}
*/