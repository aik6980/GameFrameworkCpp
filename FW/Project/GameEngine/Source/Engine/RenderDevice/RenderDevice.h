#pragma once
#ifndef RenderDevice_h__
#define RenderDevice_h__

#include "Renderer.h"

// DirectX
#include "RenderDevice/D3d11Renderer/D3d11VertexBuffer.h"

// OpenGL
#include "RenderDevice/GLRenderer/ResourceView/GLResourceView.h"
#include "RenderDevice/GLRenderer/Buffer/GLBuffer.h"
#include "RenderDevice/GLRenderer/Buffer/GLConstantBuffer.h"
#include "RenderDevice/GLRenderer/Buffer/GLVertexBuffer.h"
#include "RenderDevice/GLRenderer/Buffer/GLDrawIndirectBuffer.h"

// Forward Declaration
class CD3d11Device;

class CGLRenderTechnique;
class CGLComputeTechnique;

#endif // RenderDevice_h__