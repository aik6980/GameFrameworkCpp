#pragma once
#ifndef SpriteRenderer_h__
#define SpriteRenderer_h__

#include "BaseRenderer.h"
#include "Graphic/View/RenderView.h"
#include "Graphic/Shaders/SpriteShader.h"
#include "Graphic/GeomCreator/GeomCreator.h"

#include "Graphic/Shaders/VFXShader.h"

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

	virtual void PreRender(CGLDevice& context, RenderViewID currView);
	virtual void Render(CGLDevice& context, RenderViewID currView);

	void AddInstanceData(VFXVertex& data)	{ m_VFXVertexData.push_back(data); }
private:
	CSpriteShader*							m_Effect;

	CGLVertexBuffer<glm::vec3>				m_PosVB;
	CGLVertexBuffer<glm::vec2>				m_Tex0VB;
	CGLIndexBuffer<uint32_t>				m_IB;

	vector<CSpriteShader::INSTANCE_DATA>			m_InstanceData;
	CGLVertexBuffer<CSpriteShader::INSTANCE_DATA>	m_InstanceVB;

	// Textures
	//CTexture2DStatic*						m_TexDiffuse;

	CVFXRibbonShader*						m_VFXRibbonEffect;
	vector<VFXVertex>						m_VFXVertexData;
	CGLVertexBuffer<VFXVertex>				m_VFXVertexDataVB;
};

#endif // SpriteRenderer_h__