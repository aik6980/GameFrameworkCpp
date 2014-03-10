//--------------------------------------------------
// File:    GLTechnique.h
// Created: 01/12/2013 14:50:59
//
// Description: $
//

//--------------------------------------------------

#ifndef _GLTECHNIQUE_H__2013_12_01_14_50_59
#define _GLTECHNIQUE_H__2013_12_01_14_50_59

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////
#include "Core/Core.h"
#include "RenderDevice/GLRenderer/GLDefines.h"
#include "RenderDevice/GLRenderer/Buffer/GLVertexInputLayout.h"

// type declarations (enum struct class) //////////
class CGLCommonGpuProgram
{
public:
	CGLCommonGpuProgram();
	virtual ~CGLCommonGpuProgram();

	virtual GLint	ShaderType()=0;
	virtual void	Apply()=0;

	bool			Compile(const fs::path & fn );
	GLuint			ShaderProgramHandle() const			{ return m_ShaderProgramHandle; }
private:
	GLuint			m_ShaderProgramHandle;
	
};

class CGLVertexShader : public CGLCommonGpuProgram 
{
public:
	virtual GLint	ShaderType()	{ return GL_VERTEX_SHADER; }
	virtual void	Apply()			{};

	void SetInputLayoutDesc(const CGLVertexInputLayout& ia_desc) { m_InputLayoutDesc = ia_desc; };
	CGLVertexInputLayout& InputLayout() { return m_InputLayoutDesc; }
private:
	CGLVertexInputLayout			m_InputLayoutDesc;
};

class CGLGeometryShader : public CGLCommonGpuProgram
{
public:
	virtual GLint	ShaderType()	{ return GL_GEOMETRY_SHADER; }
	virtual void	Apply()			{};

private:
};

class CGLPixelShader : public CGLCommonGpuProgram 
{
public:
	virtual GLint	ShaderType()	{ return GL_FRAGMENT_SHADER; }
	virtual void	Apply()			{};

private:
};

class CGLComputeShader : public CGLCommonGpuProgram
{
public:
	virtual GLint	ShaderType()	{ return GL_COMPUTE_SHADER; }
	virtual void	Apply()			{};
};


class CGLRenderTechnique
{
public:
	CGLRenderTechnique();

	const string&			GetName	() const { return m_Name; }
	void					SetName(const string& val) { m_Name = val; }

	bool					Load(Renderer::ShaderType t, const fs::path & fn);
	void					Apply();

	template<class T> 
	T*						GetShader(Renderer::ShaderType type) { return static_cast<T*>(m_Shaders[type]); }	
private:
	CGLCommonGpuProgram*	CreateAndCompile( Renderer::ShaderType t, const fs::path & fn);
	bool					LinkShaders();

	string							m_Name;
	GLuint							m_TechniqueHandle;
	array<CGLCommonGpuProgram*, 6>	m_Shaders;
};


// inline file ///////////


// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _GLTECHNIQUE_H__2013_12_01_14_50_59