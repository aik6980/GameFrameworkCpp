//--------------------------------------------------
// File:    ResourceObject.h
// Created: 08/01/2014 08:46:48
//
// Description: $
//

//--------------------------------------------------

#ifndef _RESOURCEOBJECT_H__2014_01_08_08_46_47
#define _RESOURCEOBJECT_H__2014_01_08_08_46_47

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////
#include <gli/gli.hpp>
#include "Core/Core.h"

enum eResourceType
{
	UNDEFINED  = -1,
	GPUPROGRAM = 0,
	TEXTURE,
	MESH,
	NUM_RESOURCETYPE,
};

class CResourceObject
{
public:
	fs::path		m_Path;
	string			m_Name;
	eResourceType	m_Type;

	uint8_t*		m_Data;
	uint32_t		m_Size;
};

class CTextureDDSResource
{
public:
private:
	gli::storage	m_Data;
};

// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _RESOURCEOBJECT_H__2014_01_08_08_46_47