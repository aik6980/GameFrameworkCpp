// layout (binding = 2) require 420
#version 420 core

// common code
// --------------------------------
// functions
// rotation by quaternion, detail here  
// http://twistedpairdevelopment.wordpress.com/2013/02/11/rotating-a-vector-by-a-quaternion-in-glsl/
vec3 Rotation(vec4 q, vec3 v)
{
	vec3 a = cross( v, q.xyz ) + q.w * v;
	vec3 b = q.xyz;
	return v + 2.0 * cross( a, b );
} 

// uniforms
layout (binding = 0) uniform CB00
{
	mat4x4 ViewXf;
	mat4x4 ProjectionXf;
	mat4x4 ViewIXf;
	mat4x4 ProjectionIXf;
	mat4x4 ViewProjectionIXf;
}CbViewCommon;
//----------------------------------

// vertex shader code
layout (location = 0) in vec3 POSITION;
layout (location = 1) in vec2 TEXCOORD0;
layout (location = 2) in vec4 INST_POSITION;
layout (location = 3) in vec4 INST_ROTATION;

out block
{
	vec4 TexCoord0;
	vec4 Color0;
}OUT;

void main()
{
	vec4 pos		= vec4( Rotation(INST_ROTATION, POSITION * (1 + gl_InstanceID/16.0)), 1.0);
	pos.xyz			+= INST_POSITION.xyz;
	pos				= CbViewCommon.ViewXf * pos;
	pos				= CbViewCommon.ProjectionXf * pos;
	gl_Position 	= pos;
	
	// using local position for tinting
	OUT.Color0		= vec4((0.5 * POSITION.xyz + 0.5) + 0.1, 1.0); // also add small bias
}
