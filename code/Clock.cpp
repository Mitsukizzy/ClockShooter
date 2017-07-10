#include "Clock.h"
#include "graphics.h"
#include "time.h"
#include <math.h> // for cos and sin
#include <cstdlib> // for rand
#include <iostream>

#define LG_RADIUS 50
#define SM_RADIUS 2.5

Clock::Clock(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
{
	// Spawn in a random location on screen
	m_LocX = std::rand() % (m_ScreenWidth - LG_RADIUS*2) + LG_RADIUS;
	m_LocY = std::rand() % (m_ScreenHeight - LG_RADIUS*2) + LG_RADIUS;

	// Starts as a large clock
	m_IsSmall = false;

	// Pick a random speed and direction
	m_Speed = std::rand() % 5 + 1;
}


Clock::~Clock()
{
	// Clear clock draw on destroy
	int diameter = SM_RADIUS * 2;
	FillRect(m_LocX - SM_RADIUS, m_LocY - SM_RADIUS, diameter, diameter, GetRGB(0, 0, 0));

}

void Clock::Update()
{
	// Move in the current direction

	// Update draw
	DrawRing();
	DrawHour();
	DrawMinute();
}

void Clock::DrawRing()
{

}

void Clock::DrawHour()
{

}

void Clock::DrawMinute()
{

}

void Clock::CheckCollision()
{
	// If colliding with wall, reverse direction
}