#ifndef RenderVariables_inc_h__
#define RenderVariables_inc_h__

#include "Common.inc.hlsl"

cbuffer cbSceneCommon : register( b0 )
{
	float4x4 ViewXf : View;
	float4x4 ProjectionXf : Projection;
	float4x4 ViewIXf : ViewInverse;
	float4x4 ProjectionIXf : ProjectionInverse;
	float4x4 ViewProjectionIXf : ViewProjectionInverse;
}

cbuffer cbObjectCommon : register( b1 )
{
	float4x4 WorldXf : World;
	float4x4 WorldIXf : WorldInverse;
	float4x4 WorldITXf : WorldInverseTranspose;
}

float4 Transforms(out float4x4 objToProj, out float4x4 objToView, out float4x4 objToWorld, float3 posObj)
{
	objToWorld = WorldXf;
	objToView = mul(WorldXf, ViewXf);
	objToProj = mul(objToView, ProjectionXf);
	
	return mul( float4( posObj, 1.0), objToProj ); 
}

#endif // RenderVariables.inc_h__