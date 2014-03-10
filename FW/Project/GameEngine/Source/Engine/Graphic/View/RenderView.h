#pragma once
#ifndef RenderView_h__
#define RenderView_h__

class CBaseRenderer;
class CBaseCamera;
class CGLDevice;

enum RenderViewID
{
	MAINGAME_VIEW,
};

class CBaseRenderView
{
public:
	CBaseRenderView(const RenderViewID id) : 
		m_ViewID(id),
		m_pCamera(nullptr) 
	{};

	virtual void PreRender(CGLDevice& context);
	virtual void Render(CGLDevice& context)	= 0;
	virtual void PostRender(CGLDevice& context);

	const RenderViewID	GetRenderViewID	() const { return m_ViewID; }
	void				AddRenderer		(CBaseRenderer& renderer);
	void				AddCamara		(CBaseCamera& camera);
protected:
	const RenderViewID	m_ViewID;

	vector<CBaseRenderer*>		m_Renderers;
	CBaseCamera*				m_pCamera;
};

#endif // RenderView_h__