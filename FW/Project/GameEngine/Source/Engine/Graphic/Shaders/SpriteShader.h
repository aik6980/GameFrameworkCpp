#pragma once
#ifndef SpriteShader_h__
#define SpriteShader_h__

#include "BaseShader.h"
#include "Graphic/GeomCreator/GeomCreator.h"

class CSamplerState_Point;

class CSpriteShader : public CBaseRenderShader
{
public:
	struct CB02
	{
		glm::vec4	Offset;

		bool operator == (const CB02& rhs) const
		{
			bool result = (Offset == rhs.Offset);
			return result;
		}
	};

	static CGLConstantBuffer<CB02>	m_CB02;
	// Textures
	//static CTextureShaderResource	m_TexDiffuse;
	//static CSamplerState_Point		m_SamDiffuse;

	enum eTechnique
	{
		MAIN,
		MAIN_INSTANCING,
	};

	struct INSTANCE_DATA
	{
		glm::vec4 Pos;
		glm::vec4 Color;
	};

	CSpriteShader();

	void Load();
	void Unload();

	void Apply();

	eTechnique GetCurrTech() const { return m_CurrTech; }
	void SetCurrTech(eTechnique val) { m_CurrTech = val; }
private:
	eTechnique m_CurrTech;
};

#endif // SpriteShader_h__
