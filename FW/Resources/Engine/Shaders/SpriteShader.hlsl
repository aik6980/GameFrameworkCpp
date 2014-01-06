#ifndef SpriteShader_h__
#define SpriteShader_h__

#include "Common.inc.hlsl"
#include "RenderVariables.inc.hlsl"

#define SPRITE_2D

cbuffer CB02 : register( b2 )
{
	float4 Color = float4(1,0,1,1);
}

// I/O Declaration
struct VSIn
{
	float4 Pos : POSITION;
	float2 Tex0: TEXCOORD0; 
};

struct PSIn
{
	float4 Pos : SV_POSITION;
	float2 Tex0: TEXCOORD0; 
};

PSIn MainVS( VSIn IN )
{
	PSIn OUT;

	// transform
#ifndef SPRITE_2D
	float4x4 objToWorld, objToView, objToProj;
	OUT.Pos = Transforms( objToProj, objToView, objToWorld, IN.Pos.xyz);
#else
	OUT.Pos = mul(float4( IN.Pos.xyz, 1.0f), WorldXf);
#endif

	OUT.Tex0 = IN.Tex0;

	return OUT;
}

float4 MainPS( PSIn IN ) : SV_TARGET
{
	return Color;
}

// Techniques
technique11 main
{
    pass p0
	{
        SetVertexShader( CompileShader( vs_5_0, MainVS() ) );
        SetPixelShader( CompileShader( ps_5_0, MainPS() ) );
    }
}

#endif // SpriteShader_h__
