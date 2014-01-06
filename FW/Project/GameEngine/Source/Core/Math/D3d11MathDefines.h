#pragma once
#ifndef D3d11MathDefines_h__
#define D3d11MathDefines_h__

// hot hackery, we using D3DMath here
#pragma comment(lib, "d3dx11.lib")
// Core Direct3D11 interface
#include <windows.h>

// using VC debugger heap could accidentally change the Alignment, this cause problem with the SSE instructions
// #ifdef BUILD_DEBUG
// 	#define _XM_NO_INTRINSICS_
// #endif

#include <xnamath.h>

#endif // D3d11MathDefines_h__
