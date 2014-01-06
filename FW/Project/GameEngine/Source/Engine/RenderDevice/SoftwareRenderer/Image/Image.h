#pragma once
#ifndef Image_h__
#define Image_h__

#include "Core/Core.h"
#include "RenderDevice/Renderer.h"

class CImageBase
{
public:
	CImageBase()
		: m_Fmt(Renderer::IMGFMT_UNDEFINED),
		m_Width(1), 
		m_Height(1)
	{ }

	uint32_t	GetWidth()						{ return m_Width; }
	uint32_t	GetHeight()						{ return m_Height; }
	uint32_t	GetDimension()					{ return 2; }
	Renderer::ImageFormatType	GetImgFmt()		{ return m_Fmt; }

	virtual const void*			GetRawData() const = 0;
	virtual const uint32_t		GetMemPitch() const = 0;	
protected:
	uint32_t						m_Width, m_Height;
	Renderer::ImageFormatType		m_Fmt;
};

template<class T>
class CImageTemplate : public CImageBase
{
public:
	CImageTemplate()
		: m_Data(nullptr)
	{

	}
	
	virtual ~CImageTemplate()
	{
		Safe_Delete_Array(m_Data);
	}

	CImageTemplate(const CImageTemplate& rhs)
		: CImageBase(rhs),
		m_Data(nullptr)
	{
		*this = rhs;
	}

	CImageTemplate& operator = (const CImageTemplate& rhs)
	{
		CImageBase::operator = (rhs);
		Resize(rhs.m_Width, rhs.m_Height);
		memcpy(m_Data, rhs.m_Data, sizeof(T)*(m_Width*m_Height));
		return *this;
	}

	CImageTemplate(CImageTemplate&& rhs)
		: CImageBase(rhs),
		m_Data(nullptr)
	{
		*this = std::move(rhs);
	}

	CImageTemplate& operator = (CImageTemplate&& rhs)
	{
		CImageBase::operator = (rhs);
		m_Data		= rhs.m_Data;
		rhs.m_Data	= nullptr;

		return *this;
	}

	virtual const void*			GetRawData() const		{ return m_Data; }; 
	virtual const uint32_t		GetMemPitch() const		{ return sizeof(T) * m_Width; }

	void Resize( uint32_t x, uint32_t y);
	inline T& operator () (int32_t x, int32_t y)	{ return m_Data[ x + y*m_Width ]; }
protected:
	T*		m_Data;
};

template<class T>
void CImageTemplate<T>::Resize( uint32_t x, uint32_t y )
{
	Safe_Delete_Array(m_Data);
	m_Data = new T[x * y]();
	m_Width = x; m_Height = y;
}

class CImage8888;

class CImageF32 : public CImageTemplate<glm::vec4>
{
public:
	CImageF32();
	~CImageF32() {}

	CImageF32(CImageF32&& rhs) 
		: CImageTemplate<glm::vec4>(std::move(rhs))
	{ }

	CImageF32& operator = (CImageF32&& rhs)
	{
		CImageTemplate<glm::vec4>::operator=(std::move(rhs));
		return *this;
	}

	CImage8888 ToImage8888();
private:
};

class CImage8888 : public CImageTemplate<glm::uint32_t>
{
public:
	CImage8888();
	~CImage8888();

	CImage8888(CImage8888&& rhs) 
	: CImageTemplate<glm::uint32_t>(std::move(rhs))
	{ }

	CImage8888& operator = (CImage8888&& rhs)
	{
		CImageTemplate<glm::uint32_t>::operator=(std::move(rhs));
		return *this;
	}

	glm::uint32_t* GetRawData() { return m_Data; }
private:
};

#endif // Image_h__