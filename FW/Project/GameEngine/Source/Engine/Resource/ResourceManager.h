#pragma once
#ifndef ResourceManager_h__
#define ResourceManager_h__

#include "Core.h"
#include "ResourceObject.h"

class CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

	void Initialize();

	void LoadAll();
	void LoadSingleResource(const wstring& val);

	CResourceObject* Get(eResourceType t, const string& name);

	static void 	FindResourceTypeFromPath(CResourceObject & obj);
private:
	fs::path		MakeFullPath(const fs::path& val);
	wstring			FindResourceNameFromPath(CResourceObject & obj);

	static void		FindShaderTypeFromPath(CResourceObject & obj);

	fs::path			m_ResourceRoot;
	vector<fs::path>	m_ResourcePaths;

	unordered_map<string, CResourceObject> m_GPUPrograms;
};

#endif // ResourceManager_h__