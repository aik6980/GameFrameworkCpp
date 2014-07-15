#pragma once
#ifndef GLSLCompiler_h__
#define GLSLCompiler_h__

#include <string>
#include <vector>
#include <map>

using namespace std;

// boost filesystem
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;

#include "RenderDevice/RenderDevice.h"

// GL include

struct StGLSLCompilerOptions
{
	list<fs::path>	m_IncludePaths;
	fs::path		m_OutputTextFileDir;
	fs::path		m_OutputBinFileDir;
	list<fs::path>	m_OutputTextFiles;
	list<fs::path>	m_OutputBinFile;
	fs::path		m_InputFile;
};

class CGLSLCompiler
{
public:
	void Initialize(const StGLSLCompilerOptions& compilerOptions);
	void Parse();

	CGLCommonGpuProgram* Process();
private:
	bool LoadSourceFile(const wstring& fileName);
	bool Preprocessing(list<string>::iterator& it_curr_line);
	void CompileShader();

	bool LoadSourceFile(const wstring& fileName, list<string>::iterator& it_curr_line);
	void HandlePredirectiveInclude(list<string>::iterator& it_curr_line);

	void OutputPreprocessedFile(const fs::path& fileName);
	void OutputErrorFile();

	fs::path FindIncludeFile(const string& fileName);

	StGLSLCompilerOptions	m_CompilerOptions;

	list<string>			m_SourceLines;
	
	// helper			
	list<fs::path>			m_IncludeFiles;
};

#endif // GLSLCompiler_h__
