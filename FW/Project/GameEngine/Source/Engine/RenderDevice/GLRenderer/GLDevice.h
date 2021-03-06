//--------------------------------------------------
// File:    GLDevice.h
// Created: 23/10/2013 23:29:00
//
// Description: $
//

//--------------------------------------------------

#ifndef _GLDEVICE_H__2013_10_23_23_28_59
#define _GLDEVICE_H__2013_10_23_23_28_59

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////
#include "Core.h"
#include "GLDefines.h"

#include "RenderDevice/GLRenderer/Buffer/GLVertexInputLayout.h"

// forward declarations ////////////////////////////
class CGLVertexBufferCommon;

// type declarations (enum struct class) /////////
class CGLDevice
{
public:
	struct tInitStruct
	{
		HWND				hwnd;
		float				refreshRate;
		bool				bWaitForVSync;
		bool				bNeedVisualOutput;

		tInitStruct()
		{
			hwnd = nullptr;
			refreshRate = 60.0f;
			bWaitForVSync = true;
			bNeedVisualOutput = true;
		}
	};

	CGLDevice();

	void	Initialize(const tInitStruct& initData);
	void	Destroy();

	void	SwapBuffers();
	void	Clear(glm::vec4& color, float depth);

	glm::vec2 BackBufferSize();

	void	SetVertexInputLayout(const CGLVertexInputLayout& inputLayout);
	void	SetVertexBuffer(const CGLVertexBufferCommon& vb, uint32_t index);
	void	BindVertexArray();

	void	DrawArrays(Renderer::PrimitiveType mode, uint32_t base_vertex, uint32_t count);
	void	DispatchCompute(const glm::uvec3& numGroups);

	static GLenum ToGLPrimitiveType(const Renderer::PrimitiveType v);
	static GLuint ToGLType(const Renderer::DataFormat fmt);
private:
	struct VertexBufferSlotData
	{
		GLuint		BufferHandle;
		uint32_t	Stride;

		VertexBufferSlotData()
			: BufferHandle(0),
			Stride(0)
		{}
	};

	struct VertexInputLayoutData
	{
		GLuint						VAO; // VertexArrayObject (pretty much equivalent to 
		vector<CGLVertexInputElem>	VertexInputElems;

		VertexInputLayoutData()
			: VAO(0)
		{}
	};

	bool	Create30Context(const tInitStruct& initData);
	void	GetGLVersion(int32_t& major, int32_t& minor);
	static void	APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam);
	void	SetDefaultStates();

	HGLRC	m_hRC;
	HDC		m_hDC;
	HWND	m_hWnd;

	VertexInputLayoutData			m_VertexInputLayout;								
	array<VertexBufferSlotData, 8>	m_VertexInputStreams;
	array<GLuint, 16>				m_ConstantBuffers;
	
};
// public ("extern") data declarations /////////////


// public function declarations ////////////////////





// inline file ///////////


// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _GLDEVICE_H__2013_10_23_23_28_59