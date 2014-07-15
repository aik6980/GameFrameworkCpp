#include "stdafx.h"
#include "CoreCpp.h"
#include "Application/WinGameApplication.h"
#include "Global.h"
#include "Scene/World.h"
#include "Scene/Scene.h"

#include "Resource/ResourceCpp.h"
#include "Input/InputManager.h"
#include "RenderDevice/RenderDeviceCpp.h"

class MyGame : public CWinGameApplication
{
	APPLICATION_DECLARE_INITIALIZE
public:
	void OnInit(int numArgs, char** args);
	void OnUpdate();
};

APPLICATION_REGISTER_INITIALIZE( MyGame );
APPLICATION_DEFINE_INITIALIZE( MyGame, CWinGameApplication );

void MyGame::OnInit( int numArgs, char** args )
{
	if (m_CmdLineMode)
	{
		if (strcmp(args[1], "--ToolMode") == 0)
		{
			// GLSL Compiler
			CGLDevice glRenderDevice;
			{
				CGLDevice::tInitStruct initDataRenderer;
				initDataRenderer.hwnd = m_hWnd;
				initDataRenderer.bWaitForVSync = false;
				glRenderDevice.Initialize(initDataRenderer);
			}

			CGLSLCompiler glslCompiler;
			StGLSLCompilerOptions glslCompilerOptions;
			glslCompilerOptions.m_InputFile = args[2];

			glslCompiler.Initialize(glslCompilerOptions);
			CGLCommonGpuProgram* compiled_gpu_prog = glslCompiler.Process();
			Safe_Delete(compiled_gpu_prog);
		}
	}
	else
	{
		// Initialize our subsystem
		Global::SInit initData;
		initData.m_WndHandle = GetHwnd();
		initData.m_DCHandle = GetDC()->GetHDC();
		Global::Initialize(initData);
	}
}

void MyGame::OnUpdate()
{
	Global::GameTimer().Update();
	Global::InputManager().Update();
	Global::World().Update();

	// render
	Global::Scene().Render();
}

// main program entry point
int main(int numArgs, char** args)
{
	MyGame::Run(numArgs, args);
}