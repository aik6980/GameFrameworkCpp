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
	m_ResourcePaths[GPUPROGRAM] = fs::path(L"/Engine/GLSLgenerated/");
}

void CResourceManager::LoadSingleResource( const wstring& fn )
{
	CResourceObject res_obj;
	res_obj.m_Path = MakeFullPath(fn);
	res_obj.m_Name = CSTLHelper::String(FindResourceNameFromPath(res_obj));
	res_obj.m_Type = FindResourceTypeFromPath(res_obj);

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
}

fs::path CResourceManager::MakeFullPath( const fs::path& val )
{
	fs::path p;
	p /= m_ResourceRoot.wstring() + val.wstring();
	return p;
}

eResourceType CResourceManager::FindResourceTypeFromPath( CResourceObject & obj )
{
	if(obj.m_Path.wstring().find(m_ResourcePaths[GPUPROGRAM].wstring()) != -1)
	{
		return GPUPROGRAM;
	}

	return UNDEFINED;
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

