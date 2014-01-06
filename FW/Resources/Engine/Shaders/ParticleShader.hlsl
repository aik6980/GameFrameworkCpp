#ifndef ParticleFX_h__
#define ParticleFX_h__

#include "Common.inc.hlsl"
#include "RenderVariables.inc.hlsl"

cbuffer cbImmutable
{
	// pos.xy/texuv.zw
	float4 UnitQuad[4] =
	{
		float4( -1, 1, 0, 0 ),
		float4( 1, 1, 1, 0 ),
		float4( -1, -1, 0, 1),
		float4( 1, -1, 1, 1 ),
	};
};

struct VSIn
{
	float3 Pos : POSITION;
	float  Size: SIZE;
};

#define GSIn VSIn

struct PSIn
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

GSIn MainVS(VSIn IN)
{
	GSIn OUT;

	OUT.Pos	= IN.Pos;
	OUT.Size = IN.Size;

	return OUT;	
}

#define NUMVERTICES_QUAD	4
[maxvertexcount(NUMVERTICES_QUAD)]
void MainGS( point GSIn	IN[1], inout TriangleStream<PSIn> io_stream )
{
	PSIn OUT;

	// Emit 2 new triangles
	[unroll]
	for( int i=0; i<NUMVERTICES_QUAD; ++i)
	{
		// build a camera-facing quad
		float3 posL = float3( UnitQuad[i].xy * IN[0].Size, 0 );
		posL = IN[0].Pos + mul( posL, (float3x3)ViewIXf );

		// transform
		float4x4 objToWorld, objToView, objToProj;
		OUT.Pos = Transforms( objToProj, objToView, objToWorld, posL.xyz);

		OUT.Tex = UnitQuad[i].zw;

		io_stream.Append(OUT);
	}

	io_stream.RestartStrip();
}

float4 MainPS( PSIn IN ) : SV_TARGET
{
	return float4( 1, 0, 1, 1 );
}

// Techniques
technique11 main
{
    pass p0
	{
        SetVertexShader( CompileShader( vs_5_0, MainVS() ) );
        SetGeometryShader( CompileShader( gs_5_0, MainGS() ) );
        SetPixelShader( CompileShader( ps_5_0, MainPS() ) );
                
        //SetRasterizerState(WireFrame_DisableCulling);
		//SetRasterizerState(DisableCulling);    
		//SetDepthStencilState(DepthTest_WriteDisable, 0);
		//SetBlendState(DisableBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF);
    }
}


#endif // ParticleFX_h__
