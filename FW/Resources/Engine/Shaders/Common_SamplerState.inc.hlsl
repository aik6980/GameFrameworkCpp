#ifndef Common_SamplerState_inc_h__
#define Common_SamplerState_inc_h__

// Sampler States
SamplerState g_LinearSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

#define POINT_SAMPLER \
{ \
	Filter = MIN_MAG_MIP_POINT; \
    AddressU = Wrap; \
    AddressV = Wrap; \
};

SamplerState g_PointSampler_ClampUV
{
	Filter = MIN_MAG_MIP_POINT;
    AddressU = Clamp;
    AddressV = Clamp;
};

#endif // Common_SamplerState.inc_h__
