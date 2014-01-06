// local includes //////////////////////////////////
#include "stdafx.h"
#include "D3d11Technique.h"

#include "Core/CoreCpp.h"
#include "RenderDevice/D3d11Renderer/D3dMcr.h"
#include "RenderDevice/D3d11Renderer/D3d11Device.h"

CCommonGpuProgram::CCommonGpuProgram() :
m_ShaderBlob(nullptr)
{

}

bool CCommonGpuProgram::Compile( const fs::path & fn )
{
	if(!fs::exists(fn))
	{
		Debug::Print("File not found!\n");
		return false;
	}

	const string & func_name    = GetFuncname();
	const string & profile_name = GetProfile();

	uint32_t flags = 0;
	flags |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
	flags |= D3D10_SHADER_DEBUG;

	ID3D10Blob* err_blob = nullptr;
	HRESULT hr = D3DX11CompileFromFile(fn.wstring().c_str(),
		nullptr,
		nullptr,
		func_name.c_str(),
		profile_name.c_str(),
		flags,
		0,
		nullptr,
		&m_ShaderBlob,
		&err_blob,
		nullptr);

	if(FAILED(hr) || err_blob)
	{
		HR_Return(hr);
		string err_msg	= (char*)err_blob->GetBufferPointer(); 
		Debug::Print(CSTLHelper::WString(err_msg));
		return false;
	}

	return true;
}

CVertexShader::CVertexShader() : 
m_Shader(nullptr)
{

}

void CVertexShader::Apply( CD3d11Device & context )
{
	if(!m_Shader)
	{
		HRESULT hr = S_FALSE;
		hr = context.GetDevice()->CreateVertexShader(m_ShaderBlob->GetBufferPointer(), 
			m_ShaderBlob->GetBufferSize(), nullptr, &m_Shader);

		ID3D11ShaderReflection* reflectionData = nullptr;
		vector<D3D11_INPUT_ELEMENT_DESC> ia_desc = m_InputLayoutDesc.GetD3D11InputLayoutDesc();
		if(ia_desc.size() == 0)
		{
			CreateInputLayoutFromInputSignature(ia_desc, reflectionData);
		}

		hr = context.GetDevice()->CreateInputLayout(&ia_desc[0], ia_desc.size(),
			m_ShaderBlob->GetBufferPointer(), m_ShaderBlob->GetBufferSize(), &m_InputLayout);
		SafeRelease(reflectionData);
	}

	context.GetDevImmediateContext()->IASetInputLayout(m_InputLayout);
	context.GetDevImmediateContext()->VSSetShader(m_Shader, nullptr, 0);
}

bool CVertexShader::CreateInputLayoutFromInputSignature(vector<D3D11_INPUT_ELEMENT_DESC>& layoutDesc, ID3D11ShaderReflection*& reflectionData)
{
	// Reflect shader info
	if ( FAILED( D3DReflect( m_ShaderBlob->GetBufferPointer(), m_ShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &reflectionData ) ) ) 
	{
		return false;
	}

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	reflectionData->GetDesc( &shaderDesc );

	// Read input layout description from shader info
	uint32_t byteOffset = 0;
	for ( uint32_t i=0; i< shaderDesc.InputParameters; i++ )
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;       
		reflectionData->GetInputParameterDesc(i, &paramDesc );

		// fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;   
		elementDesc.SemanticName = paramDesc.SemanticName;      
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = byteOffset;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// determine DXGI format
		if ( paramDesc.Mask == 1 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
			byteOffset += 4;
		}
		else if ( paramDesc.Mask <= 3 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			byteOffset += 8;
		}
		else if ( paramDesc.Mask <= 7 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			byteOffset += 12;
		}
		else if ( paramDesc.Mask <= 15 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			byteOffset += 16;
		}

		//save element desc
		layoutDesc.push_back(elementDesc);
	}       

	//Free allocation shader reflection memory
	return true;
}

CPixelShader::CPixelShader() :
m_Shader(nullptr)
{

}

void CPixelShader::Apply( CD3d11Device & context )
{
	if(!m_Shader)
	{
		HRESULT hr = S_FALSE;
		hr = context.GetDevice()->CreatePixelShader(m_ShaderBlob->GetBufferPointer(), 
			m_ShaderBlob->GetBufferSize(), nullptr, &m_Shader);
	}

	context.GetDevImmediateContext()->PSSetShader(m_Shader, nullptr, 0);
}

void CRenderTechnique::Apply( CD3d11Device & context )
{
	context.ResetShaders();

	for_each(m_Shaders.begin(), m_Shaders.end(), 
		[&context](CCommonGpuProgram * obj)
		{
			if(obj)
				obj->Apply(context);
		});
}

bool CRenderTechnique::Load( Renderer::ShaderType t, const fs::path & fn )
{
	m_Shaders[t] = CreateAndCompile(t, fn);

	return true;
}

CCommonGpuProgram* CRenderTechnique::CreateAndCompile( Renderer::ShaderType t, const fs::path & fn)
{
	CCommonGpuProgram* newShader = nullptr;
	switch(t)
	{
	case Renderer::SHA_VERTEX_SHADER:	newShader = new CVertexShader(); break;
	case Renderer::SHA_PIXEL_SHADER:	newShader = new CPixelShader(); break;
	default:
		Debug::Assert(false, "CreateAndCompile() Failed");
		return nullptr;
	}

	newShader->Compile(fn);
	return newShader;
}

CRenderTechnique::CRenderTechnique()
{
	m_Shaders.assign(nullptr);
}

// eof /////////////////////////////////////////////




