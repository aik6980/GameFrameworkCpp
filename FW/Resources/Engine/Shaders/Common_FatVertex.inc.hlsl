#ifndef Common_FatVertex_inc_h__
#define Common_FatVertex_inc_h__

struct FatVertex
{
	float4 Position : POSITION;
	float4 Normal	: NORMAL;
	float4 TexCoord0: TEXCOORD0;
	float4 TexCoord1: TEXCOORD1;
};

#endif // Common_FatVertex.inc_h__