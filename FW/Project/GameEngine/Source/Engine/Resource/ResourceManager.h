#pragma once
#ifndef ResourceManager_h__
#define ResourceManager_h__

#include "Core.h"

enum eResourceType
{
	UNDEFINED  = -1,
	GPUPROGRAM = 0,
	TEXTURE,
	MESH,
	NUM_RESOURCETYPE,
};

class CResourceObject
{
public:
	fs::path		m_Path;
	string			m_Name;
	eResourceType	m_Type;

	uint8_t*		m_Data;
	uint32_t		m_Size;
};

class CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

	void Initialize();

	void LoadAll();
	void LoadSingleResource(const wstring& val);

	CResourceObject* Get(eResourceType t, const string& name);
private:
	fs::path		MakeFullPath(const fs::path& val);
	wstring			FindResourceNameFromPath(CResourceObject & obj);
	eResourceType	FindResourceTypeFromPath(CResourceObject & obj);

	fs::path			m_ResourceRoot;
	vector<fs::path>	m_ResourcePaths;

	unordered_map<string, CResourceObject> m_GPUPrograms;
};

#endif // ResourceManager_h__