#version 400 core

in block
{
	vec4 TexCoord0;
	vec4 Color0;
}IN;

out vec4 COLOR;

void main()
{
	COLOR = vec4(IN.TexCoord0.xyz * IN.Color0.xyz, 1);
}
