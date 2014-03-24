//--------------------------------------------------
// File:    Timer.cpp
// Created: 04/01/2014 18:33:39
//
// Description: $
//

//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h" 
#include "Timer.h" 
#include "CoreCpp.h"

CTimer::CTimer()
	: m_StartTimePoint(std::chrono::steady_clock::now())
{
	m_CurrTimePoint = m_StartTimePoint;
	m_PrevTimePoint = m_StartTimePoint;
}

void CTimer::Update()
{
	m_PrevTimePoint = m_CurrTimePoint;
	m_CurrTimePoint = std::chrono::steady_clock::now();

	// Test
	//Debug::Print((boost::wformat(TEXT("Timer Start: %1%")) % std::chrono::system_clock::to_time_t(m_StartTimePoint)));
	//Debug::Print((boost::wformat(TEXT("This Frame Time: %1%")) % GetFrameTime()));
}

float CTimer::GetFrameTime() const
{
	return std::chrono::duration<float>(m_CurrTimePoint - m_PrevTimePoint).count();
}

float CTimer::GetElapsedTime() const
{
	return std::chrono::duration<float>(m_CurrTimePoint - m_StartTimePoint).count();
}
