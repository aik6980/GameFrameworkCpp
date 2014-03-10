#pragma once
#ifndef Renderer_h__
#define Renderer_h__

#include "Core/Core.h"

class Renderer
{
public:
	// constant
	const static uint32_t	SCREEN_WIDTH	= 1024;
	const static uint32_t	SCREEN_HEIGHT	= 768;

	enum PrimitiveType
	{
		PRIM_UNDEFINED,
		PRIM_POINT,
		PRIM_LINE,
		PRIM_LINE_STRIP,
		PRIM_TRIANGLE,
		PRIM_FACE,
	};

	enum ImageFormatType
	{
		IMGFMT_UNDEFINED,
		IMGFMT_R8G8B8A8_UNORM,
		IMGFMT_R32G32B32A32_FLOAT
	};

	enum ShaderType
	{
		SHA_UNDEFINED = -1,
		SHA_VERTEX_SHADER,
		SHA_HULL_SHADER,			
		SHA_DOMAIN_SHADER,		
		SHA_GEOM_SHADER,			
		SHA_PIXEL_SHADER,		
		SHA_COMPUTE_SHADER,
	};

	enum DataFormat
	{
		SHA_FMT_VEC4_FLOAT,
		SHA_FMT_VEC3_FLOAT,
		SHA_FMT_VEC2_FLOAT,
		SHA_FMT_MAT4X4_FLOAT,
	};

	uint32_t static SizeInBytes(DataFormat fmt)
	{
		switch(fmt)
		{
		case SHA_FMT_MAT4X4_FLOAT: 
			return SizeInBytes(SHA_FMT_VEC4_FLOAT) * 4;
		case SHA_FMT_VEC4_FLOAT: 
			return sizeof(float) * 4;
		case SHA_FMT_VEC3_FLOAT:
			return sizeof(float) * 3;
		case SHA_FMT_VEC2_FLOAT:
			return sizeof(float) * 2;
		default:
			Debug::Assert(false, "Unsupported DataFormat Type");
			return 0;
		}
	}

	uint32_t static NumElems(DataFormat fmt)
	{
		switch(fmt)
		{
		case SHA_FMT_MAT4X4_FLOAT: 
			return 16;
		case SHA_FMT_VEC4_FLOAT: 
			return 4;
		case SHA_FMT_VEC3_FLOAT:
			return 3;
		case SHA_FMT_VEC2_FLOAT:
			return 2;
		default:
			Debug::Assert(false, "Unsupported DataFormat Type");
			return 0;
		}
	}

	struct ViewportDesc
	{
		glm::uvec2	TopLeft;
		uint32_t	Width;
		uint32_t	Height;
	};
};

#endif // Renderer_h__