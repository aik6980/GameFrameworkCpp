#include "stdafx.h"
#include "GLSLParser.h"
#include "Regex/Regex.h"

// Boost Wave is a C-Preprocessor Lib,
// it doesn't seem to work the way I want it to work  
//#include <boost/wave.hpp>
//#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>

/*bool Preprocess( string& dest, const string& src, const StGLSLCompilerOptions& options)
{
	// copy data we want to preprocess to dest
	string src_temp = src;

	// The template boost::wave::cpplexer::lex_token<> is the  
	// token type to be used by the Wave library.
	// This token type is one of the central types throughout 
	// the library, because it is a template parameter to some 
	// of the public classes and templates and it is returned 
	// from the iterators.
	// The template boost::wave::cpplexer::lex_iterator<> is
	// the lexer iterator to use as the token source for the
	// preprocessing engine. In this case this is parametrized
	// with the token type.
	typedef boost::wave::cpplexer::lex_iterator<
		boost::wave::cpplexer::lex_token<> >
		lex_iterator_type;
	typedef boost::wave::context<
		std::string::iterator, lex_iterator_type>
		context_type;

	context_type ctx(src_temp.begin(), src_temp.end(), "input_file");
	// set language option
	ctx.set_language(boost::wave::support_option_preserve_comments);
	ctx.set_language(boost::wave::support_option_emit_pragma_directives);

	// At this point you may want to set the parameters of the
	// preprocessing as include paths and/or predefined macros.
	{
		// add the current path
		const string local_dir	= options.m_InputFile.parent_path().string();
		const string parent_dir = options.m_InputFile.parent_path().parent_path().string();
		ctx.add_include_path(local_dir.c_str());
		ctx.add_include_path(parent_dir.c_str());

		auto first = options.m_IncludePaths.begin();
		auto end = options.m_IncludePaths.end();
		for_each(first, end, 
			[&ctx](const fs::path& obj)
			{
				ctx.add_include_path(obj.string().c_str());	
			});
	}
	//ctx.add_macro_definition(...);

	// Get the preprocessor iterators and use them to generate 
	// the token sequence.
	context_type::iterator_type first = ctx.begin();
	context_type::iterator_type last = ctx.end();

	// The input stream is preprocessed for you during iteration
	// over [first, last)
	stringstream ss;
	while(true)
	{
		try
		{
			while (first != last) {
				ss << (*first).get_value();
				++first;
			}

			if(first == last) break;
		}
		catch(const boost::wave::cpp_exception& e)
		{
			// skip this exception so we can have our user-defined #pragma
			if(e.get_errorcode() == boost::wave::preprocess_exception::ill_formed_directive)
			{
				ss << e.description();
			}
			else
			{
				cout << e.description() << endl;
				return false;
			}
		}
	}

	// output to destination string
	dest = ss.str();
	return true;
}*/

void CGLSLCompiler::Initialize( const StGLSLCompilerOptions& compilerOptions )
{
	m_CompilerOptions = compilerOptions;
}

void CGLSLCompiler::Parse()
{
	string all_contents;
	// load content from input file into a string
	ifstream input_file(m_CompilerOptions.m_InputFile.string());
	if(input_file.is_open())
	{
		// read the whole file into string
		std::string str((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
		all_contents = str;
		input_file.close();
	}

	// pre-processing
	string preprocessed_contents;
	//bool result = Preprocess(preprocessed_contents, all_contents, m_CompilerOptions);
	//if(!result)
	//{
	//	cout << "Parsing Error!" << endl;
	//	return;
	//}

	// once preprocess we add some GLSL information
	const string glsl4core = "#version 440 core\n";
	preprocessed_contents.insert(0, glsl4core);

	// parsing string
	map<string, string> source_texts;
	{
		const string expr("#pragma\\s+start\\s+(.+?)\\s+([\\s\\S]+?)#pragma\\s+end");

		vector<string> key;
		vector<string> value;
		regex_search2(preprocessed_contents, expr, key, value);

		for(unsigned int i=0;i<key.size();++i)
		{
			source_texts.insert(make_pair(key[i], value[i]));
		}
	}

}

