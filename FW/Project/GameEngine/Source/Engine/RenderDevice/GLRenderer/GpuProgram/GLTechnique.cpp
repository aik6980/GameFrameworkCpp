//--------------------------------------------------
// File:    GLTechnique.cpp
// Created: 01/12/2013 15:16:29
//
// Description: $
//

//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "GLTechnique.h" 

#include "Global.h"
#include "Resource/ResourceCpp.h"
#include "RenderDevice/GLRenderer/GLDevice.h"

CGLCommonGpuProgram::CGLCommonGpuProgram()
	: m_ShaderProgramHandle(0)
{

}

CGLCommonGpuProgram::~CGLCommonGpuProgram()
{
	glDeleteShader(m_ShaderProgramHandle);
}

bool CGLCommonGpuProgram::Compile( const fs::path & fn )
{
	// open file and load into string
	string shader_srctxt;
	ifstream input_file(fn.string());
	if(input_file.is_open())
	{
		// read the whole file into string
		std::string str((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
		shader_srctxt = str;
		input_file.close();
	}
	else
	{
		// output error
		return false;
	}

	return Compile(shader_srctxt);
}

bool CGLCommonGpuProgram::Compile(const string& src)
{
	GLint shaderType = ShaderType();
	GLuint shaderObjHandle = glCreateShader(shaderType);

	// compile
	const GLchar* shaderSrcArray[] = { src.c_str() };
	glShaderSource(shaderObjHandle, 1, shaderSrcArray, nullptr);
	glCompileShader(shaderObjHandle);

	// check if there is any error
	GLint result;
	glGetShaderiv(shaderObjHandle, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderiv(shaderObjHandle, GL_INFO_LOG_LENGTH, &result);
		char* errorStr = new char[result];

		glGetShaderInfoLog(shaderObjHandle, result, nullptr, errorStr);
		Debug::Print(boost::wformat(TEXT("glGetShaderInfoLog : %1%")) % errorStr);
		m_ErrorString = errorStr;

		Safe_Delete(errorStr);
		return false;
	}

	m_ErrorString.clear();
	m_ShaderProgramHandle = shaderObjHandle;

	return true;
}

GLint CGLCommonGpuProgram::ShaderType(const Renderer::ShaderType t)
{
	switch (t)
	{
	case Renderer::SHA_VERTEX_SHADER:	return GL_VERTEX_SHADER;
	case Renderer::SHA_GEOM_SHADER:		return GL_GEOMETRY_SHADER;
	case Renderer::SHA_PIXEL_SHADER:	return GL_FRAGMENT_SHADER;
	case Renderer::SHA_COMPUTE_SHADER:	return GL_COMPUTE_SHADER;
	default:
		Debug::Print("Unsupported Shader Type");
	}
}


CGLCommonGpuProgram* CGLTechniqueCommon::CreateAndCompile(Renderer::ShaderType t, const string& source)
{
	CGLCommonGpuProgram* newShader = nullptr;
	switch (t)
	{
	case Renderer::SHA_VERTEX_SHADER:	newShader = new CGLVertexShader(); break;
	case Renderer::SHA_GEOM_SHADER:		newShader = new CGLGeometryShader(); break;
	case Renderer::SHA_PIXEL_SHADER:	newShader = new CGLPixelShader(); break;
	case Renderer::SHA_COMPUTE_SHADER:	newShader = new CGLComputeShader(); break;
	default:
		Debug::Assert(false, "CreateAndCompile() Failed");
		return nullptr;
	}

	newShader->Compile(source);
	return newShader;
}

bool CGLTechniqueCommon::LinkShaders(CGLCommonGpuProgram** shaders, uint32_t num_elems)
{
	m_TechniqueHandle = glCreateProgram();
	for (uint32_t i = 0; i<num_elems; ++i)
	{
		if (shaders[i] && shaders[i]->ShaderProgramHandle() != 0)
		{
			glAttachShader(m_TechniqueHandle, shaders[i]->ShaderProgramHandle());
		}
	}

	glLinkProgram(m_TechniqueHandle);

	// check if there is any error
	GLint result;
	glGetProgramiv(m_TechniqueHandle, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetProgramiv(m_TechniqueHandle, GL_INFO_LOG_LENGTH, &result);
		char* errorStr = new char[result];

		glGetProgramInfoLog(m_TechniqueHandle, result, nullptr, errorStr);
		Debug::Print(boost::wformat(TEXT("glGetProgramInfoLog : %1%")) % errorStr);

		Safe_Delete(errorStr);
		return false;
	}

	return true;
}

bool CGLRenderTechnique::Load( const CResourceObject& resource_obj )
{
	Renderer::ShaderType t = resource_obj.m_ShaderType;

	CGLSLCompiler compiler;
	StGLSLCompilerOptions option;
	option.m_InputFile = resource_obj.m_Path;
	compiler.Initialize(option);

	m_Shaders[t] = compiler.Process();

	// PixelShader will be loaded at the last one, so perform linking step here 
	if(t == Renderer::SHA_PIXEL_SHADER)
	{
		return LinkShaders(&m_Shaders[0], m_Shaders.size());
	}

	return true;
}

void CGLRenderTechnique::Apply()
{
	CGLVertexShader* vs = GetShader<CGLVertexShader>(Renderer::SHA_VERTEX_SHADER);
	if(vs)
	{
		Global().Renderer().SetVertexInputLayout(vs->InputLayout());
		glUseProgram(m_TechniqueHandle);
	}
	else
	{
		glUseProgram(0);
	}
}

bool CGLComputeTechnique::Load(const CResourceObject& resource_obj)
{
	Renderer::ShaderType t = resource_obj.m_ShaderType;

	CGLSLCompiler compiler;
	StGLSLCompilerOptions option;
	option.m_InputFile = resource_obj.m_Path;
	compiler.Initialize(option);

	m_Shaders[0] = compiler.Process();

	LinkShaders(&m_Shaders[0], m_Shaders.size());

	return true;
}

void CGLComputeTechnique::Apply()
{
	CGLComputeShader* cs = static_cast<CGLComputeShader*>(m_Shaders[0]);
	if (cs)
	{
		glUseProgram(m_TechniqueHandle);
	}
	else
	{
		glUseProgram(0);
	}
}

// eof /////////////////////////////////////////////



