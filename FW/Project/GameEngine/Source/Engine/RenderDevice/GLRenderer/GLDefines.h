//--------------------------------------------------
// File:    GLDefines.h
// Created: 22/10/2013 20:19:25
//
// Description: $
//

//--------------------------------------------------

#ifndef _GLDEFINES_H__2013_10_22_20_19_25
#define _GLDEFINES_H__2013_10_22_20_19_25

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////
// using Static GLEW Lib
#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/wglew.h>

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

// type declarations (enum struct class) /////////

// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _GLDEFINES_H__2013_10_22_20_19_25