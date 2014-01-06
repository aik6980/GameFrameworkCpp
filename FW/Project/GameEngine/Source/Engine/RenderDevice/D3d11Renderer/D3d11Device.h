#pragma once
#ifndef D3d11Device_h__
#define D3d11Device_h__

#include "Core.h"
#include "D3d11Defines.h"

// define some device definition
#ifdef BUILD_DEBUG
	#define DEF_NEEDS_DEBUGDEVICE
	//#define DEF_NEEDS_NVPERFHUD
#endif

struct GpucmdClear;
class D3d11RenderSurface;

class CD3d11Device
{
public:
	struct tInitStruct
	{
		HWND				hwnd;
		D3D_FEATURE_LEVEL	featurelv;
		float				refreshRate;
		bool				bWaitForVSync;
		bool				bNeedVisualOutput;

		tInitStruct()
		{
			hwnd = NULL;
			refreshRate = 60.0f;
			bWaitForVSync = true;
			bNeedVisualOutput = true;
			featurelv = D3D_FEATURE_LEVEL_11_0;
		}
	};

	enum ColorTargetID
	{
		COLORTARGET0 = 0,
		COLORTARGET1,
		COLORTARGET2,
		MAX_COLORTARGETS		
	};

	CD3d11Device(void);
	~CD3d11Device(void);

	// GPU State
	static D3D11_DEPTH_STENCIL_DESC	GetDefaultDescDepthStencil();
	static D3D11_BLEND_DESC			GetDefaultDescBlend();
	static D3D11_RASTERIZER_DESC	GetDefaultDescRasterizer();

	void Initialize(const tInitStruct& initData);
	void Destroy();

	ID3D11Device* GetDevice() const { return m_Dev; };
	ID3D11DeviceContext* GetDevImmediateContext() const { return m_ImmidiateContext; };

	void SwapBuffers();

	D3D11_TEXTURE2D_DESC		GetBackBufferDesc() { return m_backBufferDesc; };
	ID3D11RenderTargetView*		GetBackBufferRTV() { return m_BackBufferRTV; };
	ID3D11DepthStencilView*		GetBackBufferDSV() { return m_BackBufferDSV; };

	// Operation
	void ClearColor(GpucmdClear& _cmd);
	void ClearDepth(GpucmdClear& _cmd);

	void SetRenderTarget(const D3d11RenderSurface& _rt);

	bool IsBindedVS();
	bool IsBindedGS();
	bool IsBindedPS();

	// resource function
	void CreateBuffer(ID3D11Buffer*& buffer, const D3D11_BUFFER_DESC& desc, void* pData);
	void CreateConstantBuffer(ID3D11Buffer*& buffer, size_t size, void* pData);

	// render pipeline
	void ResetShaders();
private:
	// myNote: get backBuffer description as texture 2d
	D3D11_TEXTURE2D_DESC GetBackBufferDesc_Internal();
	// require functionalities for MSAA - Alpha to coverage
	// myNote: DXGI_SURFACE_DESC will be retrieved from the SwapChains, by
	// simply convert from Texture2D Desc 
	// (referred to DXUT.cpp, DXUTUpdateBackBufferDesc(), seem like we cannot get DXGI_DESC directly)  
	DXGI_SURFACE_DESC GetDXGISurfaceDesc();

	// function to setup the rendering pipeline
	void CreateDevice();
	void CreateSwapChain(DXGI_SWAP_CHAIN_DESC* _sd);
	void CreateRenderTargetView(ID3D11RenderTargetView** _renderTargetView);
	void CreateDepthStencilView(ID3D11DepthStencilView** _depthStencilView);
	void SetupOutputMerger();

	// read only InitialData
	tInitStruct m_InitConfig; 

	// Direct3D10 Low-level interface DXGI (Graphic card Management)
	IDXGIFactory* m_AdapterFactory;
	// simply the abstracted layer of the render device
	// Note: D3D11 API, the device and the context are separated, this way we could
	// assign multiple contexts per device for multithreaded rendering.
	ID3D11Device* m_Dev;
	ID3D11DeviceContext* m_ImmidiateContext;
	// the graphic interface, that take control of the double-buffering
	IDXGISwapChain*				m_SwapChain;
	ID3D11RenderTargetView*		m_BackBufferRTV;
	ID3D11DepthStencilView*		m_BackBufferDSV;

	// GPU States
	ID3D11RenderTargetView**	m_RenderTargetViews[MAX_COLORTARGETS];
	ID3D11DepthStencilView**	m_DepthStencilView;

	ID3D11DepthStencilState*	m_stateDepthStencil;
	ID3D11BlendState*			m_stateBlend;
	ID3D11RasterizerState*		m_stateRasterizer;

	// Back buffer desc
	D3D11_TEXTURE2D_DESC		m_backBufferDesc;
};

#endif // CD3d11Device_h__


