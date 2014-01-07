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

// GL include


struct StGLSLCompilerOptions
{
	vector<fs::path>	m_IncludePaths;
	fs::path			m_OutputTextFileDir;
	fs::path			m_OutputBinFileDir;
	vector<fs::path>	m_OutputTextFiles;
	vector<fs::path>	m_OutputBinFile;
	fs::path			m_InputFile;
};

class CGLSLCompiler
{
public:
	void Initialize(const StGLSLCompilerOptions& compilerOptions);
	void Parse();
private:
	void CompileShader(string str);

	StGLSLCompilerOptions m_CompilerOptions;
};

#endif // GLSLCompiler_h__
