#pragma once
#ifndef VFXShader_h__
#define VFXShader_h__

#include "BaseShader.h"
#include "Graphic/GeomCreator/GeomCreator.h"

struct VFXVertex
{
	glm::vec4	Position;
	glm::vec4	Color;
};

class CVFXRibbonShader : public CBaseRenderShader
{
public:
	enum eTechnique
	{
		MAIN,
	};

	CVFXRibbonShader();

	void Load();
	void Unload();

	void Apply();

	eTechnique GetCurrTech() const { return m_CurrTech; }
	void SetCurrTech(eTechnique val) { m_CurrTech = val; }
private:
	eTechnique m_CurrTech;
};

#endif