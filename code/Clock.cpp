#include "Clock.h"
#include "graphics.h"
#include "time.h"
#include <math.h> // for cos and sin
#include <cstdlib> // for rand
#include <iostream>
#include <time.h>       /* time */

#define LG_RADIUS 50
#define SM_RADIUS 2.5

Clock::Clock(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
{
	std::srand(time(NULL) );

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
	int d = m_IsSmall ? (SM_RADIUS * 2) : (LG_RADIUS * 2);
	int r = m_IsSmall ? SM_RADIUS : LG_RADIUS;
	FillRect(m_LocX - r, m_LocY - r, d+1, d+1, GetRGB(0, 0, 0));

	// Move in the current direction
	m_LocX += 1;

	// Update draw
	DrawRing();
	DrawHour();
	DrawMinute();
}

void Clock::DrawRing()
{
	//static const double PI = 3.1415926535;
	//double i, angle, x1, y1, x2, y2;
	//int r = m_IsSmall ? SM_RADIUS : LG_RADIUS;

	//for(i = 0; i < 360; i += 2)
	//{
	//	angle = i;
	//	x1 = r * cos(angle * PI / 180);
	//	y1 = r * sin(angle * PI / 180);
	//	angle += 1;
	//	x2 = r * cos(angle * PI / 180);
	//	y2 = r * sin(angle * PI / 180);
	//	DrawLine(x1 + m_LocX, y1 + m_LocY, x2 + m_LocX, y2 + m_LocY, GetRGB( 255, 255, 255 ));
	//}
}

void Clock::DrawHour()
{

}

void Clock::DrawMinute()
{

}

void Clock::CheckCollision()
{
	int r = m_IsSmall ? SM_RADIUS : LG_RADIUS;
	// If colliding with wall, reverse direction
	if ((m_LocX - r < 0) || (m_LocX + r > m_ScreenWidth) || (m_LocY - r < 0) || (m_LocY + r > m_ScreenHeight))
	{

	}
}