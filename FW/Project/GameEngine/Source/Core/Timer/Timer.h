//--------------------------------------------------
// File:    Timer.h
// Created: 04/01/2014 18:33:13
//
// Description: $
//

//--------------------------------------------------

#ifndef _TIMER_H__2014_01_04_18_33_13
#define _TIMER_H__2014_01_04_18_33_13

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////

//  C++11 timer utility
// http://en.cppreference.com/w/cpp/chrono
#include <chrono>
#include <ctime>

// type declarations (enum struct class) /////////
class CTimer
{
public:
	CTimer();

	void  Update();

	float GetFrameTime() const;
	float GetElapsedTime() const;
private:
	std::chrono::time_point<std::chrono::system_clock>	m_StartTimePoint;
	std::chrono::time_point<std::chrono::system_clock>	m_CurrTimePoint;
	std::chrono::time_point<std::chrono::system_clock>	m_PrevTimePoint;
};


// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _TIMER_H__2014_01_04_18_33_13