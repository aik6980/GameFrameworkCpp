//--------------------------------------------------
// File:    RigidShader.h
// Created: 03/01/2014 12:23:25
//
// Description: $
//

//--------------------------------------------------

#ifndef _RIGIDSHADER_H__2014_01_03_12_23_25
#define _RIGIDSHADER_H__2014_01_03_12_23_25

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////
#include "Core/Core.h"
#include "BaseShader.h"

// type declarations (enum struct class) /////////
class CRigidShader : public CBaseRenderShader
{
public:
	enum eTechnique
	{
		MAIN_INSTANCING,
	};

	struct INSTANCE_DATA
	{
		glm::vec4 Pos;
		glm::vec4 Rotation;
	};

	CRigidShader();

	void Load();
	void Unload();

	void Apply();

	eTechnique GetCurrTech() const { return m_CurrTech; }
	void SetCurrTech(eTechnique val) { m_CurrTech = val; }
private:
	eTechnique m_CurrTech;
};


// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _RIGIDSHADER_H__2014_01_03_12_23_25