#pragma once
#ifndef TargetDefines_h__
#define TargetDefines_h__

// common definition for this whole solution
// application setting
//#define DEF_HAVECONSOLE

#if defined(_DEBUG) || defined(DEBUG)
#define  BUILD_DEBUG
#endif

// compiler predefined directive
#define _VC2010COMPILER_	(_MSC_VER == 1600)
#define _VC2012COMPILER_	(_MSC_VER == 1700)
#define _VC2013COMPILER_	(_MSC_VER == 1800)
#define _INTELCOMPILER_		(__INTEL_COMPILER)	


#endif // TargetDefines_h__