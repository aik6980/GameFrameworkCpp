// layout (binding = 2) require 420
#version 420 core

// uniforms
layout (binding = 0) uniform CB00
{
    mat4x4 ViewXf;
    mat4x4 ProjectionXf;
    mat4x4 ViewIXf;
    mat4x4 ProjectionIXf;
    mat4x4 ViewProjectionIXf;
}CbViewCommon;

// static 

// stage input/output
in block
{
    vec4 Color0;
}IN[];

out block
{
    vec4 Texcoord0;
    vec4 Color0;
}OUT;

// [ lines_adjacency ] note
//  + -------- + ======== + -------- +
// gl_in[3]	 gl_in[2]  gl_in[1]   gl_in[0]

// Specify the input and output primitive types, along
// with the maximum number of vertices that this shader
// might produce.
layout (lines_adjacency) in;
layout (triangle_strip, max_vertices = 8)out;

void main()
{
    const float thickness = 0.1;

    vec3 l01 = (gl_in[2].gl_Position - gl_in[3].gl_Position).xyz;
    vec3 l12 = (gl_in[1].gl_Position - gl_in[2].gl_Position).xyz;
    vec3 l23 = (gl_in[0].gl_Position - gl_in[1].gl_Position).xyz;

    vec3 v1 = cross(vec3(0,0,1), normalize(l01 + l12));
    vec3 v2 = cross(vec3(0,0,1), normalize(l12 + l23));
    vec3 v3 = cross(vec3(0,0,1), normalize(l23));

    //v1 = normalize(v1+v2);
    //v2 = normalize(v2+v3);

    vec3 base = gl_in[2].gl_Position.xyz;

    gl_Position = vec4(base + v1 * thickness * 0.5, 1.0);
    OUT.Color0 = IN[0].Color0;
    EmitVertex();
    gl_Position = vec4(base - v1 * thickness * 0.5, 1.0);
    OUT.Color0 = IN[0].Color0;
    EmitVertex();
    gl_Position = vec4(base + v2 * thickness * 0.5 + l12, 1.0);
    OUT.Color0 = IN[1].Color0;
    EmitVertex();
    gl_Position = vec4(base - v2 * thickness * 0.5 + l12, 1.0);
    OUT.Color0 = IN[1].Color0;
    EmitVertex();

    EndPrimitive();
}
