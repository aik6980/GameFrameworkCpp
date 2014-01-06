#pragma once
#ifndef GpuCmd_h__
#define GpuCmd_h__

#include "Core/Core.h"
#include "Core/Math/Math.h"

struct GpucmdClear
{
	glm::vec4	ClearColorVal;
	float		ClearDepthVal;
	byte		ClearStencilVal;

	GpucmdClear()
		: ClearColorVal( glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f )),
		ClearDepthVal( 1.0f ),
		ClearStencilVal( 0 )
	{}
};

#endif // GpuCmd_h__