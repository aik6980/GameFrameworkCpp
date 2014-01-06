#pragma once
#ifndef SpriteRenderer_h__
#define SpriteRenderer_h__

#include "BaseRenderer.h"
#include "Graphic/View/RenderView.h"
#include "Graphic/Shaders/SpriteShader.h"
#include "Graphic/GeomCreator/GeomCreator.h"

#include "RenderDevice/RenderDevice.h"

class CSprite;
class CMeshData;
class CTexture2DStatic;

class CSpriteRenderer : public CBaseRenderer
{
public:
	CSpriteRenderer() : CBaseRenderer(SPRITE_RENDERER) { Init(); };
	
	~CSpriteRenderer()
	{
		//Safe_Delete(m_TexDiffuse);
		Safe_Delete(m_Effect);
	}

	void Init();
	void Render(CGLDevice& context, RenderViewID currView);
private:
	CSpriteShader*							m_Effect;

	CGLVertexBuffer<glm::vec3>				m_PosVB;
	CGLVertexBuffer<glm::vec2>				m_Tex0VB;
	CGLIndexBuffer<uint32_t>				m_IB;

	vector<CSpriteShader::INSTANCE_DATA>			m_InstanceData;
	CGLVertexBuffer<CSpriteShader::INSTANCE_DATA>	m_InstanceVB;

	// Textures
	//CTexture2DStatic*						m_TexDiffuse;
};

#endif // SpriteRenderer_h__