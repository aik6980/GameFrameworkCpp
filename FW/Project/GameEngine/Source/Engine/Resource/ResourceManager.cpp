//--------------------------------------------------
// File:    ResourceManager.cpp
// Created: 03/02/2013 21:28:12
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "ResourceManager.h" 

#include "Core/CoreCpp.h"

CResourceManager::CResourceManager()
{

}

void CResourceManager::Initialize()
{
	m_ResourceRoot = FileSystem::GetResourcesPath();

	m_ResourcePaths.resize(NUM_RESOURCETYPE);
	m_ResourcePaths[GPUPROGRAM] = fs::path(L"/Engine/glsl/");
}

void CResourceManager::LoadSingleResource( const wstring& fn )
{
	CResourceObject res_obj;
	res_obj.m_Path = MakeFullPath(fn);
	res_obj.m_Name = CSTLHelper::String(FindResourceNameFromPath(res_obj));
	FindResourceTypeFromPath(res_obj);

	m_GPUPrograms.insert(std::make_pair(res_obj.m_Name, res_obj));
}

void CResourceManager::LoadAll()
{
	// Load All GPU Program
	LoadSingleResource(m_ResourcePaths[GPUPROGRAM].wstring() + L"SpriteShader.vs.glsl");
	LoadSingleResource(m_ResourcePaths[GPUPROGRAM].wstring() + L"SpriteShader.ps.glsl");
	LoadSingleResource(m_ResourcePaths[GPUPROGRAM].wstring() + L"RigidShader.vs.glsl");
	LoadSingleResource(m_ResourcePaths[GPUPROGRAM].wstring() + L"RigidShader.ps.glsl");
	LoadSingleResource(m_ResourcePaths[GPUPROGRAM].wstring() + L"ParticleGS.vs.glsl");
	LoadSingleResource(m_ResourcePaths[GPUPROGRAM].wstring() + L"ParticleGS.gs.glsl");
	LoadSingleResource(m_ResourcePaths[GPUPROGRAM].wstring() + L"ParticleGS.ps.glsl");
	// Compute
	LoadSingleResource(m_ResourcePaths[GPUPROGRAM].wstring() + L"ParticleEmit.cs.glsl");
	LoadSingleResource(m_ResourcePaths[GPUPROGRAM].wstring() + L"ParticleSimulation.cs.glsl");
}

fs::path CResourceManager::MakeFullPath( const fs::path& val )
{
	fs::path p;
	p /= m_ResourceRoot.wstring() + val.wstring();
	return p;
}

void CResourceManager::FindResourceTypeFromPath( CResourceObject & obj )
{
	if(obj.m_Path.extension().string() == ".glsl")
	{
		obj.m_Type = GPUPROGRAM;
		FindShaderTypeFromPath(obj);
	}

	obj.m_Type = UNDEFINED;
}

void CResourceManager::FindShaderTypeFromPath(CResourceObject & obj)
{
	Debug::Assert(obj.m_Type == GPUPROGRAM, "ShaderType is only available for GPUPROGRAM");

	// find subtype
	const string& shader_type_str = obj.m_Path.stem().extension().string();
	if (shader_type_str == ".vs")
	{
		obj.m_ShaderType = Renderer::SHA_VERTEX_SHADER;
	}
	else if (shader_type_str == ".gs")
	{
		obj.m_ShaderType = Renderer::SHA_GEOM_SHADER;
	}
	else if (shader_type_str == ".ps")
	{
		obj.m_ShaderType = Renderer::SHA_PIXEL_SHADER;
	}
	else if (shader_type_str == ".cs")
	{
		obj.m_ShaderType = Renderer::SHA_COMPUTE_SHADER;
	}
	else
	{
		Debug::Print("Unsupported ShaderType");
	}
}

std::wstring CResourceManager::FindResourceNameFromPath( CResourceObject & obj )
{
	wstring name = obj.m_Path.filename().wstring();
	uint32_t ext_pos = name.rfind(L".");
	if(ext_pos != string::npos)
	{
		name = name.substr(0, ext_pos);
	}

	return name;
}

CResourceObject* CResourceManager::Get( eResourceType t, const string& name )
{
	switch(t)
	{
	case GPUPROGRAM:
		{
			auto r = m_GPUPrograms.find(name);
			if(r!=m_GPUPrograms.end()) return &(r->second);
		}
		break;
	}

	return nullptr;
}



// eof /////////////////////////////////////////////

