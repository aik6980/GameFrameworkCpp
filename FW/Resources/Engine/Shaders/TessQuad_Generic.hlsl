#include "Common.inc.hlsl"
#include "Common_FatVertex.inc.hlsl"
#include "RenderVariables.inc.hlsl"

cbuffer cbTess_Generic
{
	float g_TessFactor = 1.0;
};

// Struct
struct VSOut
{
	float4 Position : SV_POSITION;
};


// Output from Hull Shader
struct HSOutConst
{
	float TessFactor[4] : SV_TessFactor;
	float InsideTessFactor[2] : SV_InsideTessFactor;
};

// Functions

// Pass-Through VS
FatVertex Tess_GenericVS(FatVertex IN)
{
	FatVertex OUT = (FatVertex)0;
	OUT.Position = float4(IN.Position.xyz * 0.5f, 1.0);
	
	return OUT;
}

// Hull Shader
HSOutConst Tess_GenericHSConst( InputPatch<FatVertex, 4> IN )
{
	HSOutConst OUT = (HSOutConst)0;
	
	OUT.TessFactor[0] = OUT.TessFactor[1] = OUT.TessFactor[2] = OUT.TessFactor[3] = g_TessFactor;
	OUT.InsideTessFactor[0] = OUT.InsideTessFactor[1] = g_TessFactor;
	
	return OUT;
}

[domain("quad")]
// [Q?] fraction_even! fraction_odd find out more more these different scheme
[partitioning("integer")]
[outputtopology("triangle_cw")]
[patchconstantfunc("Tess_GenericHSConst")]
[outputcontrolpoints(4)]
// Note: CPID => Constant Patch ID?
FatVertex Tess_GenericHS( InputPatch<FatVertex, 4> IN,
	uint uCPID : SV_OutputControlPointID )
{
	FatVertex OUT = (FatVertex)0;;
	OUT.Position = IN[uCPID].Position;
	
	return OUT;
}

// Domain Shader
[domain("quad")]
VSOut Tess_GenericDS( HSOutConst HSConstData, OutputPatch<FatVertex, 4> IN,
	float2 barycentricCoords : SV_DomainLocation )
{
	VSOut OUT;
	
	// first interpolation to get the vertex position
	float3 v1 = lerp( IN[0].Position, IN[1].Position, barycentricCoords.x ).xyz;
	float3 v2 = lerp( IN[2].Position, IN[3].Position, barycentricCoords.x ).xyz;
	float3 posObj = lerp( v1, v2, barycentricCoords.y);
	
	// here we do displacement map
	
	// output like normally we do to VertexShader
	float4x4 objToWorld, objToView, objToProj;
	OUT.Position = Transforms( objToProj, objToView, objToWorld, posObj.xyz);

	//OUT.Position = float4( posObj.xyz, 1.0);
	
	return OUT;
}

float4 Tess_GenericPS( VSOut IN ) : SV_TARGET0 
{
	return float4( 1.0, 0, 1.0, 1.0);
} 


// Techniques (for test compile only)
technique11 main
{
	pass p0
	{
        SetVertexShader( CompileShader( vs_5_0, Tess_GenericVS() ) );
		SetHullShader( CompileShader( hs_5_0, Tess_GenericHS() ) );
		SetDomainShader( CompileShader( ds_5_0, Tess_GenericDS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, Tess_GenericPS() ) );
                
        //SetRasterizerState(WireFrame_DisableCulling);  
		//SetDepthStencilState(DepthTest_WriteDisable, 0);
		//SetBlendState(DisableBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF);
    }
}
