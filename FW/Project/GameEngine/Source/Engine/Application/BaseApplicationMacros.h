#pragma once
#ifndef BaseApplicationMacros_h__
#define BaseApplicationMacros_h__

//----------------------------------------------------------------------------
#define APPLICATION_DECLARE_INITIALIZE \
public: \
	static bool Initialize ();

//----------------------------------------------------------------------------
#define APPLICATION_REGISTER_INITIALIZE(classname) \
	bool ms_bInitializeRegistered = \
	classname::Initialize ();

//----------------------------------------------------------------------------
#define APPLICATION_DEFINE_INITIALIZE(classname, framework) \
	bool classname::Initialize () \
{ \
	CBaseApplication::Run = &framework::Run; \
	CBaseApplication::INSTANCE = new classname(); \
	return true; \
}

#endif // BaseApplicationMacros_h__

