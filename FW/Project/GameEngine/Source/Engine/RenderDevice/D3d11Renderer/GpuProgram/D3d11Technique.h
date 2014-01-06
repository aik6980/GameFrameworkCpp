#pragma once
#ifndef D3d11Technique_h__
#define D3d11Technique_h__

#include "RenderDevice/Renderer.h"
#include "RenderDevice/D3d11Renderer/D3d11Defines.h"
#include "RenderDevice/D3d11Renderer/GpuProgram/D3d11GpuProgParam.h"

class CVertexShader;
class CGeometryShader;
class CHullShader;
class CDomainShader;
class CPixelShader;

class CD3d11Device;

class CCommonGpuProgram
{
public:
	CCommonGpuProgram();

	virtual const string GetProfile()=0;
	virtual const string GetFuncname()=0;

	virtual void Apply(CD3d11Device & context)=0;

	bool Compile(const fs::path & fn );
protected:
	ID3D10Blob* m_ShaderBlob;
};

class CVertexShader : public CCommonGpuProgram
{
public:
	CVertexShader();

	const string  GetProfile()	{ return "vs_5_0"; }
	const string  GetFuncname()	{ return "MainVS"; }

	void Apply(CD3d11Device & context);

	void SetInputLayoutDesc(const CInputLayoutDesc& ia_desc) { m_InputLayoutDesc = ia_desc; };
private:
	bool CreateInputLayoutFromInputSignature(vector<D3D11_INPUT_ELEMENT_DESC>& layoutDesc, ID3D11ShaderReflection*& reflectionData);

	ID3D11VertexShader*			m_Shader;

	CInputLayoutDesc			m_InputLayoutDesc;
	ID3D11InputLayout*			m_InputLayout;
};

class CPixelShader : public CCommonGpuProgram
{
public:
	CPixelShader();

	const string  GetProfile()	{ return "ps_5_0"; }
	const string  GetFuncname()	{ return "MainPS"; }

	void Apply(CD3d11Device & context);
private:
	ID3D11PixelShader* m_Shader;
};

class CRenderTechnique
{
public:
	CRenderTechnique();

	const string& GetName() const { return m_Name; }
	void SetName(const string& val) { m_Name = val; }

	bool Load(Renderer::ShaderType t, const fs::path & fn);

	void Apply( CD3d11Device & context);

	template<class T> 
	T* GetShader(Renderer::ShaderType type) { return static_cast<T*>(m_Shaders[type]); }
private:
	CCommonGpuProgram* CreateAndCompile(Renderer::ShaderType t, const fs::path & fn);

	string							m_Name;
	array<CCommonGpuProgram*, 6>	m_Shaders;
};

#endif // D3d11Technique_h__