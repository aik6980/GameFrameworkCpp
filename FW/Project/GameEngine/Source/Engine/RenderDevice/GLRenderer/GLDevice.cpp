//--------------------------------------------------
// File:    GLDevice.cpp
// Created: 23/10/2013 23:29:20
//
// Description: $
//

//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "GLDevice.h" 

#include "RenderDevice/GLRenderer/Buffer/GLVertexBuffer.h"

CGLDevice::CGLDevice()
	: m_hRC(0),
	m_hDC(0),
	m_hWnd(0)
{

}

void CGLDevice::Initialize( const tInitStruct& initData )
{
	// Create modern GL context
	Create30Context(initData);
	// Set default states
	SetDefaultStates();
}

bool CGLDevice::Create30Context( const tInitStruct& initData )
{
	// store some variables
	m_hWnd = initData.hwnd;
	m_hDC = GetDC(m_hWnd);

	// choose PixelFormat
	PIXELFORMATDESCRIPTOR pfd; // Create a new PIXELFORMATDESCRIPTOR (PFD)
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)); // Clear our  PFD
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); // Set the size of the PFD to the size of the class
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW; // Enable double buffering, opengl support and drawing to a window
	pfd.iPixelType = PFD_TYPE_RGBA; // Set our application to use RGBA pixels
	pfd.cColorBits = 32; // Give us 32 bits of color information (the higher, the more colors)
	pfd.cDepthBits = 32; // Give us 32 bits of depth information (the higher, the more depth levels)
	pfd.iLayerType = PFD_MAIN_PLANE; // Set the layer of the PFD

	int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd); // Check if our PFD is valid and get a pixel format back
	if (nPixelFormat == 0) // If it fails
		return false;

	BOOL bResult = SetPixelFormat(m_hDC, nPixelFormat, &pfd); // Try and set the pixel format based on our PFD
	if (bResult == 0) // If it fails
		return false;

	HGLRC tempOpenGLContext = wglCreateContext(m_hDC); // Create an OpenGL 2.1 context for our device context
	wglMakeCurrent(m_hDC, tempOpenGLContext); // Make the OpenGL 2.1 context current and active

	// init GLEW (Have to be done after create a default Context)
	GLenum error = glewInit(); // Enable GLEW
	if (error != GLEW_OK) // If GLEW fails
		return false;

	// get OpenGL version
	int32_t major, minor;
	GetGLVersion(major, minor);

	// *note* highly suggested to use CORE_PROFILE instead of COMPATIBLE_PROFILE
	uint32_t context_flags = WGL_CONTEXT_DEBUG_BIT_ARB
		//| WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB // Set our OpenGL context to be forward compatible
		;

	int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major, // Set the MAJOR version of OpenGL to 4
		WGL_CONTEXT_MINOR_VERSION_ARB, minor, // Set the MINOR version of OpenGL to 2
		// *note* highly suggested to use CORE_PROFILE instead of COMPATIBLE_PROFILE
		WGL_CONTEXT_FLAGS_ARB, context_flags,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1) { // If the OpenGL 3.x context creation extension is available
		m_hRC = wglCreateContextAttribsARB(m_hDC, NULL, attributes); // Create and OpenGL 3.x context based on the given attributes
		wglMakeCurrent(NULL, NULL); // Remove the temporary context from being active
		wglDeleteContext(tempOpenGLContext); // Delete the temporary OpenGL 2.1 context
		wglMakeCurrent(m_hDC, m_hRC); // Make our OpenGL 3.0 context current
	}
	else {
		m_hRC = tempOpenGLContext; // If we didn't have support for OpenGL 3.x and up, use the OpenGL 2.1 context
	}

	int glVersion[2] = {-1, -1}; // Set some default values for the version
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]); // Get back the OpenGL MAJOR version we are using
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]); // Get back the OpenGL MAJOR version we are using

	Debug::Print((boost::wformat(TEXT("Using OpenGL: %1%.%2%")) % glVersion[0] % glVersion[1])); // Output which version of OpenGL we are using

	// setup debug context
	if (context_flags & WGL_CONTEXT_DEBUG_BIT_ARB)
	{
		if (glDebugMessageCallback)
		{
			auto func = &CGLDevice::GLDebugCallback;
			glDebugMessageCallback(func, nullptr);
		}
	}

	// get window info
	glm::vec2 vp_size = BackBufferSize();
	glViewport(0,0,(int32_t)vp_size.x, (int32_t)vp_size.y);

	// setup v-sync
	// http://www.3dbuzz.com/forum/threads/188320-Enable-or-Disable-VSync-in-OpenGL
	if(wglSwapIntervalEXT)
	{
		if(initData.bWaitForVSync)
		{
			wglSwapIntervalEXT(1);
		}
		else
		{
			wglSwapIntervalEXT(0);
		}
	}

	return true;
}

void CGLDevice::Destroy()
{
	wglMakeCurrent(m_hDC, 0); // Remove the rendering context from our device context
	wglDeleteContext(m_hRC); // Delete our rendering context
}

void CGLDevice::GetGLVersion( int32_t& major, int32_t& minor )
{
	// for all versions
	char* ver = (char*)glGetString(GL_VERSION); // ver = "3.2.0"
	
	major = ver[0] - '0';
	if( major >= 3)
	{
		// for GL 3.x
		glGetIntegerv(GL_MAJOR_VERSION, &major); // major = 3
		glGetIntegerv(GL_MINOR_VERSION, &minor); // minor = 2
	}
	else
	{
		minor = ver[2] - '0';
	}
	// GLSL
	ver = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION); // ver = "1.50 NVIDIA via Cg compiler"
	Debug::Print(boost::wformat(TEXT("GL_SHADING_LANGUAGE_VERSION : %1%")) % ver);
}

void CGLDevice::BindVertexArray()
{
	glBindVertexArray(m_VertexInputLayout.VAO);

	GLuint lastLocationUsed = 0;
	for(uint32_t attrib=0; attrib<m_VertexInputLayout.VertexInputElems.size(); ++attrib)
	{
		const CGLVertexInputElem& inputElem = m_VertexInputLayout.VertexInputElems[attrib];
		GLuint bufferHandle = m_VertexInputStreams[inputElem.InputSlot].BufferHandle;
		uint32_t stride		= m_VertexInputStreams[inputElem.InputSlot].Stride;
		glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);

		glVertexAttribPointer(inputElem.LayoutLocation,
			Renderer::NumElems(inputElem.Fmt), ToGLType(inputElem.Fmt), GL_FALSE, 
			stride, (const GLvoid*)inputElem.AlignedBytesOffset);
		glVertexAttribDivisor(inputElem.LayoutLocation, inputElem.InstanceDataStepRate);
		glEnableVertexAttribArray(inputElem.LayoutLocation);

		lastLocationUsed = inputElem.LayoutLocation;
	}

	// disable the rest of attributes
	for(uint32_t attrib=lastLocationUsed+1; attrib<8; ++attrib)
	{
		glDisableVertexAttribArray(attrib);
	}
}

GLenum CGLDevice::ToGLPrimitiveType(const Renderer::PrimitiveType v)
{
	switch (v)
	{
	case Renderer::PRIM_POINT:							return GL_POINT;
	case Renderer::PRIM_LINE:							return GL_LINES;
	case Renderer::PRIM_LINE_ADJACENCY:					return GL_LINES_ADJACENCY;
	case Renderer::PRIM_LINE_STRIP:						return GL_LINE_STRIP;
	case Renderer::PRIM_LINE_STRIP_ADJACENCY:			return GL_LINE_STRIP_ADJACENCY;
	case Renderer::PRIM_TRIANGLE:						return GL_TRIANGLES;
	default:
		Debug::Assert(false, "Unsupported Type");
		return 0;
	}
}

GLuint CGLDevice::ToGLType(const Renderer::DataFormat fmt)
{
	switch(fmt)
	{
	case Renderer::SHA_FMT_MAT4X4_FLOAT: 
	case Renderer::SHA_FMT_VEC4_FLOAT: 
	case Renderer::SHA_FMT_VEC3_FLOAT:
	case Renderer::SHA_FMT_VEC2_FLOAT:
		return GL_FLOAT;
	default:
		Debug::Assert(false, "Unsupported DataFormat Type");
		return 0;
	}
}

void CGLDevice::Clear( glm::vec4& color, float depth )
{
	// Clear color buffer with black
	glClearColor(color.r, color.g, color.b, color.a);
	glClearDepth(depth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CGLDevice::SwapBuffers()
{
	glFlush();
	::SwapBuffers(m_hDC);
}

void CGLDevice::SetVertexBuffer( const CGLVertexBufferCommon& vb, uint32_t index )
{
	VertexBufferSlotData vbData;
	vbData.BufferHandle = vb.BufferHandle();
	vbData.Stride		= vb.Stride();

	m_VertexInputStreams[index] = vbData;
}

void CGLDevice::SetVertexInputLayout( const CGLVertexInputLayout& inputLayout )
{
	m_VertexInputLayout.VAO					= inputLayout.VAO();
	m_VertexInputLayout.VertexInputElems	= inputLayout.Elems();
}

void CGLDevice::SetDefaultStates()
{
	glEnable(GL_DEPTH_TEST);
	// OpenGL clipping is [-1, 1] including z-axis (while DirectX is [0, 1] on the z) 
	//if(glDepthRangedNV)
	//{
		// there is a way to eliminate the bias by (indirectly) setting the mapping function via the glDepthRangedNV call with -1, 1 arguments, 
		// which effectively sets the DirectX-style mapping.
		// http://outerra.blogspot.co.uk/2012/11/maximizing-depth-buffer-range-and.html
		// glDepthRangedNV(-1.0, 1.0);
	//}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void CGLDevice::DrawArrays(Renderer::PrimitiveType mode, uint32_t base_vertex, uint32_t count)
{
	if (!count)
		return;

	BindVertexArray();
	glDrawArrays(ToGLPrimitiveType(mode), base_vertex, count);
}

void CGLDevice::DispatchCompute(const glm::uvec3& numGroups)
{
	glDispatchCompute(numGroups.x, numGroups.y, numGroups.z);
}

glm::vec2 CGLDevice::BackBufferSize()
{
	RECT rc;
	GetClientRect(m_hWnd, &rc);

	int vpWidth = rc.right - rc.left;
	int vpHeight = rc.bottom - rc.top;

	return glm::vec2(vpWidth, vpHeight);
}

void CGLDevice::GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam)
{
	Debug::Print(boost::wformat(TEXT("Debug message with source 0x%04X, type 0x%04X, id %u, severity 0x%0X, '%s'\n")) 
		% source % type % id % severity % message);
}





