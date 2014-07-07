#include "stdafx.h"
#include "CoreCpp.h"
#include "Application/WinGameApplication.h"
#include "Global.h"
#include "Scene/World.h"
#include "Scene/Scene.h"

#include "Resource/ResourceCpp.h"
#include "Input/InputManager.h"

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
	// Initialize our subsystem
	Global::SInit initData;
	initData.m_WndHandle	= GetHwnd();
	initData.m_DCHandle		= GetDC()->GetHDC();
	Global::Initialize(initData);
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
	if(numArgs>1)
	{
		if(strcmp(args[1], "--ToolMode")==0)
		{
			Debug::Print("Start ToolMode");

			// GLSL Compiler
			CGLSLCompiler glslCompiler;
			StGLSLCompilerOptions glslCompilerOptions;
			glslCompilerOptions.m_InputFile = args[2];

			glslCompiler.Initialize(glslCompilerOptions);
			glslCompiler.Process();
		}
	}
	else
	{
		Debug::Print("Start GameMode");
		MyGame::Run(0, NULL);
	}
}