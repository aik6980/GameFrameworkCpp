#ifndef	SHARED_INC_GLSL
#define	SHARED_INC_GLSL

// uniforms
layout (binding = 0) uniform CB00
{
    mat4x4 ViewXf;
    mat4x4 ProjectionXf;
    mat4x4 ViewIXf;
    mat4x4 ProjectionIXf;
    mat4x4 ViewProjectionIXf;
}CbViewCommon;

#endif