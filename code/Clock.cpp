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
	std::srand(time(NULL));

	// Spawn in a random location on screen
	m_Pos.x = std::rand() % (m_ScreenWidth - LG_RADIUS*2) + LG_RADIUS;
	m_Pos.y = std::rand() % (m_ScreenHeight - LG_RADIUS*2) + LG_RADIUS;

	// Starts as a large clock
	m_IsSmall = false;

	// Pick a random speed and direction
	//m_Speed = std::rand() % 5 + 1;
	m_Speed = 0.2f;
	int angle = std::rand() % 360;

	m_Dir.x = sin( angle );
	m_Dir.y = -cos( angle );
}


Clock::~Clock()
{
	// Clear clock draw on destroy
	int diameter = SM_RADIUS * 2;
	FillRect(m_Pos.x - SM_RADIUS, m_Pos.y - SM_RADIUS, diameter, diameter, GetRGB(0, 0, 0));
}

void Clock::Update()
{
	int d = m_IsSmall ? (SM_RADIUS * 2) : (LG_RADIUS * 2);
	int r = m_IsSmall ? SM_RADIUS : LG_RADIUS;
	FillRect(m_Pos.x - r, m_Pos.y - r, d+1, d+1, GetRGB(0, 0, 0));

	CheckCollision();

	// Move in the current direction
	m_Pos = m_Pos + m_Dir * m_Speed;

	//std::cout << "POS: " << m_Pos.x << ", " << m_Pos.y << std::endl;
	//std::cout << "DIR: " << m_Dir.x << ", " << m_Dir.y << std::endl;

	int hour, min, sec;
	GetTime( hour, min, sec );

	// Update draw
	DrawRing();
	DrawHour(hour);
	DrawMinute(min);
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

	int d = m_IsSmall ? (SM_RADIUS * 2) : (LG_RADIUS * 2);
	float r = m_IsSmall ? SM_RADIUS : LG_RADIUS;

	// Top
	DrawLine(m_Pos.x - r, m_Pos.y - r, m_Pos.x + r, m_Pos.y - r, GetRGB( 255, 255, 255 ));
	// Right
	DrawLine(m_Pos.x + r, m_Pos.y - r, m_Pos.x + r, m_Pos.y + r, GetRGB( 255, 255, 255 ));
	// Bottom
	DrawLine(m_Pos.x - r, m_Pos.y + r, m_Pos.x + r, m_Pos.y + r, GetRGB( 255, 255, 255 ));
	// Left
	DrawLine(m_Pos.x - r, m_Pos.y - r, m_Pos.x - r, m_Pos.y + r, GetRGB( 255, 255, 255 ));
}

void Clock::DrawHour(int hour)
{
	Vector2 v_hr;
	float div = hour / 12.0f;
	float r = m_IsSmall ? SM_RADIUS : LG_RADIUS;

	DrawLine(m_Pos.x, m_Pos.y, m_Pos.x - r, m_Pos.y + r, GetRGB( 255, 255, 255 ));
}

void Clock::DrawMinute(int min)
{

}

void Clock::CheckCollision()
{
	int r = m_IsSmall ? SM_RADIUS : LG_RADIUS;
	// If colliding with wall, reverse direction
	if ((m_Pos.x - r < 0) || (m_Pos.x + r > m_ScreenWidth) )
	{
		m_Dir.x *= -1;
	}
	else if((m_Pos.y - r < 0) || (m_Pos.y + r > m_ScreenHeight))
	{
		m_Dir.y *= -1;
	}
}