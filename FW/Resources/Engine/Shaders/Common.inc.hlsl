#ifndef Common_inc_h__
#define Common_inc_h__

#include "Common_SamplerState.inc.hlsl"

// Common operation
#define ConvertSNormToUVCoord(v) (0.5*(v) + 0.5)
#define ConvertUVCoordToSNorm(v) (2*(v) - 1)

#endif // Common.inc_h__
