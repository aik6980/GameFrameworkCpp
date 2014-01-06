#include "stdafx.h"
#include "D3d11Device.h"
#include "D3dMcr.h"

#include "Device3DCommand/Device3DCmd.h"
#include "Surface/D3d11Surface.h"
#include "GpuProgram/D3d11GpuProgParam.h"

CD3d11Device::CD3d11Device(void)
	: m_BackBufferRTV(nullptr),
	m_BackBufferDSV(nullptr)
{
	m_AdapterFactory = nullptr;
	m_Dev = nullptr;
	m_SwapChain = nullptr;

	ZeroMemory(m_RenderTargetViews, sizeof(m_RenderTargetViews));
	m_DepthStencilView = nullptr;
}

CD3d11Device::~CD3d11Device(void)
{	
	SafeRelease(m_BackBufferRTV);
	SafeRelease(m_BackBufferDSV);
	SafeRelease(m_SwapChain);
	SafeRelease(m_Dev);
	SafeRelease(m_AdapterFactory);
}

void CD3d11Device::Initialize(const tInitStruct& initData )
{
	m_InitConfig = initData;

	HWND hwnd = initData.hwnd;
	// get window info
	RECT rc;
	GetClientRect(hwnd,&rc);

	int vpWidth = rc.right - rc.left;
	int vpHeight= rc.bottom - rc.top;

	// create D3D10 Device and SwapChain
	CreateDevice();

	// for tools, we might dont need to draw but still need to build a device context
	if(initData.bNeedVisualOutput == true)
	{
		// create swap chain description
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory( &sd, sizeof(sd));

		sd.BufferCount			= 1;
		/// Note: sd.BufferDesc.Format -> 
		/// http://msdn.microsoft.com/en-us/library/bb173059(VS.85).aspx
		///
		sd.BufferDesc.Width		= vpWidth;
		sd.BufferDesc.Height	= vpHeight;
		sd.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;

		UINT refreshRate = m_InitConfig.bWaitForVSync ? (UINT)m_InitConfig.refreshRate : 0;
		sd.BufferDesc.RefreshRate.Numerator = refreshRate;
		
		sd.BufferDesc.RefreshRate.Denominator = 1;
		// note: DX_GI : Graphic Infrastructure
		sd.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow			= hwnd;
		sd.SampleDesc.Count		= 1;
		sd.SampleDesc.Quality	= 0;
		sd.Windowed				= true;
		sd.SwapEffect			= DXGI_SWAP_EFFECT_DISCARD;

		CreateSwapChain(&sd);
		// create render target view
		CreateRenderTargetView(&m_BackBufferRTV);
		m_RenderTargetViews[COLORTARGET0] = &m_BackBufferRTV;
		// create depthStencil texture
		CreateDepthStencilView(&m_BackBufferDSV);
		m_DepthStencilView = &m_BackBufferDSV;
		// setup output view port
		SetupOutputMerger();

		// setup dafault states
		{
			D3D11_DEPTH_STENCIL_DESC desc = GetDefaultDescDepthStencil();
			m_Dev->CreateDepthStencilState(&desc, &m_stateDepthStencil);
			m_ImmidiateContext->OMSetDepthStencilState(m_stateDepthStencil, 0);
		}

		// initialize other rendering stuffs
		m_backBufferDesc = GetBackBufferDesc_Internal();
	}
}

void CD3d11Device::CreateDevice()
{
	HRESULT hr;
	// Supporting NVPerfHUD
	SafeRelease(m_AdapterFactory);
	IDXGIFactory *pDXGIFactory = 0;
	hr = HR_Return(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory));
	m_AdapterFactory = pDXGIFactory;

	// Looking for an adapter 
	// If it is present, override default settings
	UINT nAdapter = 0;
	ID3D11Device* pDevice = NULL;
	IDXGIAdapter* adapter = NULL; 
	IDXGIAdapter* selectedAdapter = NULL; 

	// D3D11 Note: from August 2009
	/*
	Differences between Direct3D 10 and Direct3D 11:

	In Direct3D 10, the presence of pAdapter dictated which adapter to use and the DriverType could mismatch what the adapter was.

	In Direct3D 11, if you are trying to create a hardware or a software device, set pAdapter != NULL which constrains the other inputs to be:

	DriverType must be D3D_DRIVER_TYPE_UNKNOWN 
	Software must be NULL. 
	On the otherhand, if pAdapter == NULL, the DriverType cannot be set to D3D_DRIVER_TYPE_UNKNOWN; it can be set to either:

	If DriverType == D3D_DRIVER_TYPE_SOFTWARE, Software cannot be NULL. 
	If DriverType == D3D_DRIVER_TYPE_HARDWARE, the adapter used will be equivalent to the one returned by pAdapterIDXGIFactory::EnumAdapters( 0, ... ). 
	*/
	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_UNKNOWN;

	while (pDXGIFactory->EnumAdapters(nAdapter, &adapter) != 
		DXGI_ERROR_NOT_FOUND) 
	{ 
		if (adapter) 
		{ 
			DXGI_ADAPTER_DESC adaptDesc; 
			if (SUCCEEDED(adapter->GetDesc(&adaptDesc))) 
			{ 			
#ifdef DEF_NEEDS_NVPERFHUD
				// Search for a PerfHUD adapter.   
				const bool isPerfHUD = wcscmp(adaptDesc.Description, L"NVIDIA PerfHUD") == 0; 
				// Select the first adapter in normal circumstances or the PerfHUD one if it 
				// exists. 
				if(isPerfHUD)
				{
					selectedAdapter = adapter; 
					driverType = D3D10_DRIVER_TYPE_REFERENCE; 
				}
#else
				// select the first adapter we found
				selectedAdapter = adapter; 
#endif
				break;
			} 
		} 
		++nAdapter; 
	} 

	// set DX10 creat flag base on configuration
	UINT createFlags = NULL; 
#ifdef DEF_NEEDS_DEBUGDEVICE
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL wantedFeatureSet[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
	D3D_FEATURE_LEVEL supportedFeatureSet = (D3D_FEATURE_LEVEL)0x0; // this will hold what level we actually support  

	ID3D11DeviceContext* immidiateContext = NULL;

	hr = HR_Return(D3D11CreateDevice( selectedAdapter, 
		driverType, 
		NULL, 
		createFlags, 
		wantedFeatureSet, 
		ARRAYSIZE(wantedFeatureSet),
		D3D11_SDK_VERSION,
		&pDevice,
		&supportedFeatureSet,
		&immidiateContext));

	// report

	// store Direct3DDevice
	m_Dev = pDevice;
	m_ImmidiateContext = immidiateContext;
}

void CD3d11Device::CreateSwapChain( DXGI_SWAP_CHAIN_DESC* _sd )
{
	HRESULT hr = S_OK;
	SafeRelease(m_SwapChain);
	// Create the swap chain
	hr = HR_Return(m_AdapterFactory->CreateSwapChain( m_Dev, _sd, &m_SwapChain ));
}

void CD3d11Device::CreateRenderTargetView( ID3D11RenderTargetView** _renderTargetView )
{
	ID3D11Texture2D* backBuffer;
	m_SwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	m_Dev->CreateRenderTargetView(backBuffer,0,
		_renderTargetView);
	SafeRelease(backBuffer);
}

void CD3d11Device::CreateDepthStencilView( ID3D11DepthStencilView** _depthStencilView )
{
	HRESULT hr;

	DXGI_SURFACE_DESC backBufferDesc = GetDXGISurfaceDesc();

	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory( &descDepth, sizeof(descDepth));

	descDepth.ArraySize = 1;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	// DXGI_FORMAT_D32_FLOAT : Depth 32bit, no Stencil
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.Height = backBufferDesc.Height;
	descDepth.MipLevels = 1;
	descDepth.MiscFlags = 0;
	descDepth.SampleDesc.Count = backBufferDesc.SampleDesc.Count;
	descDepth.SampleDesc.Quality = backBufferDesc.SampleDesc.Quality;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.Width = backBufferDesc.Width;

	ID3D11Texture2D* depthTex2d;
	hr = HR_Return(m_Dev->CreateTexture2D(&descDepth,0,&depthTex2d));

	// Note: using NULL, to tell D3D that we want to use DepthBuffer texture config
	// mk:@MSITStore:C:\Program%20Files%20(x86)\Microsoft%20DirectX%20SDK%20(February%202010)\Documentation\DirectX9\windows_graphics.chm::/ID3D11Device_CreateDepthStencilView.htm
	hr = HR_Return(m_Dev->CreateDepthStencilView(depthTex2d,NULL,
		&m_BackBufferDSV));
	SafeRelease(depthTex2d);
}

DXGI_SURFACE_DESC CD3d11Device::GetDXGISurfaceDesc()
{
	DXGI_SURFACE_DESC backBufferSurfaceDesc;
	D3D11_TEXTURE2D_DESC TexDesc = GetBackBufferDesc_Internal();
	backBufferSurfaceDesc.Width = ( UINT )TexDesc.Width;
	backBufferSurfaceDesc.Height = ( UINT )TexDesc.Height;
	backBufferSurfaceDesc.Format = TexDesc.Format;
	backBufferSurfaceDesc.SampleDesc = TexDesc.SampleDesc;

	return backBufferSurfaceDesc;
}

D3D11_TEXTURE2D_DESC CD3d11Device::GetBackBufferDesc_Internal()
{
	HRESULT hr;
	ID3D11Texture2D* pBackBuffer;
	hr = m_SwapChain->GetBuffer( 0, __uuidof( *pBackBuffer ), ( LPVOID* )&pBackBuffer );
	D3D11_TEXTURE2D_DESC backBufferSurfaceDesc;
	if( SUCCEEDED( hr ) )
	{
		pBackBuffer->GetDesc( &backBufferSurfaceDesc );
		// release after used
		SafeRelease( pBackBuffer );
	}

	return backBufferSurfaceDesc;
}

void CD3d11Device::SetupOutputMerger()
{
	// note: OM : Output Merger
	// OMSetRenderTargets() will not increase the reference counting
	m_ImmidiateContext->OMSetRenderTargets(1,
		*m_RenderTargetViews,*m_DepthStencilView);

	DXGI_SURFACE_DESC backBufferDesc = GetDXGISurfaceDesc();

	// setup view port
	D3D11_VIEWPORT vp;
	vp.Width = (float)backBufferDesc.Width;
	vp.Height= (float)backBufferDesc.Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	m_ImmidiateContext->RSSetViewports(1,&vp);
}

void CD3d11Device::SwapBuffers()
{
	HR_Return(m_SwapChain->Present(m_InitConfig.bWaitForVSync, 0));
}

D3D11_DEPTH_STENCIL_DESC CD3d11Device::GetDefaultDescDepthStencil()
{
	D3D11_DEPTH_STENCIL_DESC desc;

	desc.DepthEnable		= TRUE;
	desc.DepthWriteMask		= D3D11_DEPTH_WRITE_MASK_ALL; // depth write, ON
	desc.DepthFunc			= D3D11_COMPARISON_LESS_EQUAL;
	
	desc.StencilEnable		= FALSE;
	desc.StencilReadMask	= D3D11_DEFAULT_STENCIL_READ_MASK;	// 0xff, always pass
	desc.StencilWriteMask	= D3D11_DEFAULT_STENCIL_WRITE_MASK;	// 0xff, always pass

	D3D11_DEPTH_STENCILOP_DESC opdesc = 
	{  
		D3D11_STENCIL_OP_KEEP, 
		D3D11_STENCIL_OP_KEEP,
		D3D11_STENCIL_OP_KEEP,
		D3D11_COMPARISON_ALWAYS
	};
	desc.FrontFace	= opdesc; 
	desc.BackFace	= opdesc;

	return desc;
}

D3D11_BLEND_DESC CD3d11Device::GetDefaultDescBlend()
{
	D3D11_BLEND_DESC desc;

	desc.AlphaToCoverageEnable = FALSE;
	desc.IndependentBlendEnable = FALSE; // all RTs is blended using similar setup

#define MAINRT 0 
	desc.RenderTarget[MAINRT].BlendEnable = FALSE;
	desc.RenderTarget[MAINRT].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	desc.RenderTarget[MAINRT].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[MAINRT].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[MAINRT].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[MAINRT].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[MAINRT].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[MAINRT].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
#undef MAINRT

	return desc;
}

D3D11_RASTERIZER_DESC CD3d11Device::GetDefaultDescRasterizer()
{
	D3D11_RASTERIZER_DESC desc;

	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = FALSE; // following the left-handed system
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.0f; // maximum depth bias, 0.0f means no clamp 
	desc.SlopeScaledDepthBias = 0.0f;
	desc.DepthClipEnable = TRUE;
	desc.ScissorEnable = FALSE;
	desc.MultisampleEnable = FALSE;
	desc.AntialiasedLineEnable = FALSE;

	return desc; 
}

void CD3d11Device::ClearColor( GpucmdClear& _cmd )
{
	m_ImmidiateContext->ClearRenderTargetView( *m_RenderTargetViews[COLORTARGET0], &_cmd.ClearColorVal[0] );
}

void CD3d11Device::ClearDepth( GpucmdClear& _cmd )
{
	m_ImmidiateContext->ClearDepthStencilView( *m_DepthStencilView, D3D11_CLEAR_DEPTH,
		_cmd.ClearDepthVal, _cmd.ClearStencilVal );
}

// void CD3d11Device::SetRenderTarget( const D3d11RenderSurface& _rt )
// {
// 	D3D11_TEXTURE2D_DESC rtDesc;
// 	_rt.GetColorBuffer()->m_Resource->GetDesc(&rtDesc);
// 
// 	D3D11_VIEWPORT vp;
// 	::ZeroMemory (&vp, sizeof (vp));
// 	vp.Width = rtDesc.Width;
// 	vp.Height = rtDesc.Height;
// 	vp.MaxDepth = 1.0f;
// 
// 	m_ImmidiateContext->OMSetRenderTargets (1, &_rt.GetColorBuffer()->m_RTV, _rt.GetDepthBuffer()->m_RTV);
// 	m_ImmidiateContext->RSSetViewports (1, &vp);
// }

void CD3d11Device::CreateBuffer( ID3D11Buffer*& buffer, const D3D11_BUFFER_DESC& desc, void* pData)
{
	D3D11_SUBRESOURCE_DATA data_info;
	ZeroMemory(&data_info, sizeof(data_info));
	data_info.pSysMem = pData;

	HRESULT hr = m_Dev->CreateBuffer( &desc, &data_info, &buffer );
	if( FAILED( hr ) )
	{
		Debug::Print(L"Failed to create a buffer.");
	}
}

void CD3d11Device::CreateConstantBuffer( ID3D11Buffer*& buffer, size_t size, void* pData)
{
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = size;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data_info;
	ZeroMemory(&data_info, sizeof(data_info));
	data_info.pSysMem = pData;
	
	HRESULT hr = m_Dev->CreateBuffer( &desc, &data_info, &buffer );
	if( FAILED( hr ) )
	{
		Debug::Print(L"Failed to create constant buffer.");
	}
}

bool CD3d11Device::IsBindedVS()
{
	bool result = false;
	ID3D11VertexShader* shader = nullptr;
	m_ImmidiateContext->VSGetShader(&shader, nullptr, 0);
	if(shader != nullptr)
	{ 
		result = true;
		SafeRelease(shader);
	}

	return result;
}

bool CD3d11Device::IsBindedPS()
{
	bool result = false;
	ID3D11PixelShader* shader = nullptr;
	m_ImmidiateContext->PSGetShader(&shader, nullptr, 0);
	if(shader != nullptr)
	{ 
		result = true;
		SafeRelease(shader);
	}

	return result;
}

void CD3d11Device::ResetShaders()
{
	m_ImmidiateContext->VSSetShader(nullptr, nullptr, 0);
	m_ImmidiateContext->HSSetShader(nullptr, nullptr, 0);
	m_ImmidiateContext->DSSetShader(nullptr, nullptr, 0);
	m_ImmidiateContext->GSSetShader(nullptr, nullptr, 0);
	m_ImmidiateContext->PSSetShader(nullptr, nullptr, 0);
	m_ImmidiateContext->CSSetShader(nullptr, nullptr, 0);
}



