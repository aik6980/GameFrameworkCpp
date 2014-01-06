#pragma once
#ifndef DX11Defines_h__
#define DX11Defines_h__

#pragma comment(lib, "dxerr.lib")

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

// for DXUT SdkMesh 
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "comctl32.lib")

#pragma comment(lib, "DXGI.lib")

#pragma comment(lib, "dxguid.lib")

// The library need Win32
#include <Windows.h>

// DirectX Error
#include <DxErr.h>

// Core Direct3D11 interface
#include <D3D11.h>
#include <D3DX11.h>

// Effect system
#include <D3Dcompiler.h>
#include <D3D11Shader.h>
#pragma comment(lib, "d3dcompiler.lib")

// Low-level device manager
// myNote: more information at, 
// http://msdn.microsoft.com/en-us/library/bb205075(VS.85).aspx
#include <DXGI.h>

#endif // DX11Defines_h__