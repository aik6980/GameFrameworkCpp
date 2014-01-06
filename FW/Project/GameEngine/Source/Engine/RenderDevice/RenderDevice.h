#pragma once
#ifndef RenderDevice_h__
#define RenderDevice_h__

#include "Renderer.h"

// DirectX
#include "RenderDevice/D3d11Renderer/D3d11VertexBuffer.h"

// OpenGL
#include "RenderDevice/GLRenderer/Buffer/GLConstantBuffer.h"
#include "RenderDevice/GLRenderer/Buffer/GLVertexBuffer.h"

// Forward Declaration
class CD3d11Device;

class CGLRenderTechnique;

#endif // RenderDevice_h__