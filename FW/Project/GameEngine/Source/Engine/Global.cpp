#include "stdafx.h" 
#include "Global.h"

#include "Core/CoreCpp.h"
#include "Physics/PhysicsCpp.h"
#include "Resource/ResourceManager.h"
#include "RenderDevice/RenderDeviceCpp.h"
#include "Input/InputManager.h"

#include "Scene/Scene.h"
#include "Scene/World.h"

CResourceManager*	Global::m_ResourceManager	= new CResourceManager();
CGLDevice*			Global::m_GLRenderer		= new CGLDevice();
CInputManager*		Global::m_InputManager		= nullptr;

CParticleManager*	Global::m_ParticleManager	= new CParticleManager();
CRigidBodyManager*	Global::m_RigidBodyManager  = new CRigidBodyManager();

CScene*				Global::m_Scene				= new CScene();
CWorld*				Global::m_World				= new CWorld();
CTimer*				Global::m_GameTimer			= new CTimer();

void Global::Initialize(const SInit& initData )
{
	m_ResourceManager->Initialize();
	m_ResourceManager->LoadAll();

	m_InputManager = new CInputManager(initData.m_WndHandle);

	/*
	{
		CD3d11Device::tInitStruct initDataRenderer;
		initDataRenderer.hwnd = initData.Hwnd;
		m_Renderer->Initialize(initDataRenderer);
	}
	*/

	{
		CGLDevice::tInitStruct initDataRenderer;
		initDataRenderer.hwnd = initData.m_WndHandle;
		initDataRenderer.bWaitForVSync = false;
		m_GLRenderer->Initialize(initDataRenderer);
	}

	m_ParticleManager->Initialize();

	// High level system (Game Logic, etc.)
	m_Scene->Initialize();
	m_World->Initialize();
}

void Global::Destroy()
{

}




