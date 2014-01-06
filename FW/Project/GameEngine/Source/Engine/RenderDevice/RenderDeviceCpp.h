#pragma once
#ifndef RenderDeviceCpp_h__
#define RenderDeviceCpp_h__

#include "RenderDevice.h"

// Software Renderer
#include "SoftwareRenderer/Image/Image.h"

// D3D11 Renderer
#include "D3d11Renderer/D3d11Device.h"
#include "D3d11Renderer/GpuProgram/D3d11SamplerState.h"
#include "D3d11Renderer/GpuProgram/D3d11Technique.h"
#include "D3d11Renderer/Surface/D3d11Texture2D.h"
#include "D3d11Renderer/Device3DCommand/Device3DCmd.h"

// OpenGL Renderer
#include "GLRenderer/GLDevice.h"
#include "GLRenderer/GpuProgram/GLTechnique.h"
#include "GLRenderer/Buffer/GLVertexInputLayout.h"
#include "GLRenderer/Buffer/GLVertexBuffer.h"
#include "GLRenderer/Buffer/GLConstantBuffer.h"

#endif // RenderDeviceCpp_h__