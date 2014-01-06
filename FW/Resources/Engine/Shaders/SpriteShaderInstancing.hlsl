#ifndef SpriteShader_h__
#define SpriteShader_h__

#include "Common.inc.hlsl"
#include "RenderVariables.inc.hlsl"

#define SPRITE_2D

// Constant Buffer
Texture2D		TexDiffuse	: register( t0 );
SamplerState	SamDiffuse  : register( s0 );

// I/O Declaration
struct VSIn
{
	float4 Pos			: POSITION;
	float2 Tex0			: TEXCOORD0;
};

struct VSIn_Instance
{
	float4 Pos		: INST_POSITION; 		
	float4 Color	: INST_COLOR;
	uint   Inst_ID	: SV_InstanceID;
};

struct PSIn
{
	float4 Pos		: SV_POSITION;
	float2 Tex0		: TEXCOORD0;
	float4 Color	: TEXCOORD1;
};

PSIn MainVS( VSIn IN, VSIn_Instance IN1)
{
	PSIn OUT;

	// transform
#ifndef SPRITE_2D
	float4x4 objToWorld, objToView, objToProj;
	OUT.Pos = Transforms( objToProj, objToView, objToWorld, IN.Pos.xyz);
#else
	float4x4 mat = 
	{ IN1.Pos.w,0,0,0,
	0,IN1.Pos.w,0,0,
	0,0,IN1.Pos.w,0,
	IN1.Pos.xyz,1 };

	float scale = (IN1.Inst_ID > 1) ? 2 : 1;

	OUT.Pos = mul(float4( IN.Pos.xyz * scale, 1.0f), mat);
#endif

	OUT.Tex0 = IN.Tex0;
	OUT.Color= IN1.Color;

	return OUT;
}

float4 MainPS( PSIn IN ) : SV_TARGET
{
	float4 col = TexDiffuse.Sample(SamDiffuse, IN.Tex0) * IN.Color;
	return col;
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
