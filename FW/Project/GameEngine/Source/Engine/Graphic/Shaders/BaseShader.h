#pragma once
#ifndef BaseShader_h__
#define BaseShader_h__

#include "RenderDevice/RenderDevice.h"

class CBaseCamera;

// Common Variables
struct cbViewCommon
{
	glm::fmat4x4 ViewXf;
	glm::fmat4x4 ProjectionXf;
	glm::fmat4x4 ViewIXf;
	glm::fmat4x4 ProjectionIXf;
	glm::fmat4x4 ViewProjectionIXf;

	bool operator == (const cbViewCommon& rhs) const
	{
		bool result = (ViewXf == rhs.ViewXf) &&
			(ProjectionXf == rhs.ProjectionXf) &&
			(ViewIXf == rhs.ViewIXf) &&
			(ProjectionIXf == rhs.ProjectionIXf) &&
			(ViewProjectionIXf == rhs.ViewProjectionIXf);
		return result;
	}
};

struct cbObjectCommon
{
	glm::fmat4x4 WorldXf;
	glm::fmat4x4 WorldIXf;
	glm::fmat4x4 WorldITXf;
};

class CBaseShader
{
public:
	CBaseShader();

	static CGLConstantBuffer<cbViewCommon>		m_CbViewCommon;
	//static CGLConstantBuffer<cbObjectCommon>	m_CbObjectCommon;

	virtual	const string & GetName()	{ return m_Name; }

	static void SetViewCommonData(const CBaseCamera& camera);
protected:
	string		m_Name;

	std::unordered_map<int32_t, CGLRenderTechnique*>	m_RenderTechniques;
};

#endif // BaseShader_h__