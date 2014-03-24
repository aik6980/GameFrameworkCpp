#pragma once
#ifndef Global_h__
#define Global_h__

#include "Core/Core.h"

class CD3d11Device;
class CGLDevice;
class CResourceManager;
class CInputManager;

class CParticleManager;
class CRigidBodyManager;

class CScene;
class CWorld;
class CTimer;

class Global
{
public:
	struct SInit
	{
		HWND	m_WndHandle;
		HDC		m_DCHandle;
	};

	static void Initialize(const SInit& init);
	static void Destroy();

	static CGLDevice &			Renderer()			{ return *m_GLRenderer; }
	static CResourceManager &	ResourceManager()	{ return *m_ResourceManager; }
	static CInputManager &		InputManager()		{ return *m_InputManager; }
	static CParticleManager &	ParticleManager()	{ return *m_ParticleManager; }
	static CRigidBodyManager &	RigidBodyManager()	{ return *m_RigidBodyManager; }

	static CScene &				Scene()				{ return *m_Scene; }
	static CWorld &				World()				{ return *m_World; }
	static CTimer &				GameTimer()			{ return *m_GameTimer; }

private:
	// subsystems
	static CResourceManager*	m_ResourceManager;
	static CGLDevice*			m_GLRenderer;
	static CInputManager*		m_InputManager;

	static CParticleManager*	m_ParticleManager;
	static CRigidBodyManager*	m_RigidBodyManager;

	static CScene*				m_Scene;
	static CWorld*				m_World;
	static CTimer*				m_GameTimer;
};

#endif // Global_h__