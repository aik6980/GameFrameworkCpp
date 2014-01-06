// #version 440 core - will be added by shader tool
#pragma start common
// common code
float4 common_float

#pragma end

#pragma start vertex_shader

#include "SharedVS.glsl"

#define FOO 2

// vertex shader code
void main()
{
	float a = FOO;
}

#pragma end

#pragma start pixel_shader
// pixel shader


#pragma end
