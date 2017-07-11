#include "Clock.h"
#include "graphics.h"
#include "time.h"
#include <math.h> // for cos and sin
#include <cstdlib> // for rand
#include <iostream>
#include <ctime>       /* time */

#define LG_RADIUS 50
#define SM_RADIUS 2.5

static const float k_PI = 3.1415926536f;

Clock::Clock(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
{
	std::srand(std::time(0));
	m_isAlive = true;

	// Spawn in a random location on screen
	m_Pos.x = std::rand() % (m_ScreenWidth - LG_RADIUS*2) + LG_RADIUS;
	m_Pos.y = std::rand() % (m_ScreenHeight - LG_RADIUS*2) + LG_RADIUS;

	// Starts as a large clock
	m_Radius = LG_RADIUS;

	// Pick a random speed and direction
	m_Speed = std::rand() % 5 + 1;

	int angle = std::rand() % 360;
	m_Dir.x = sin( angle );
	m_Dir.y = -cos( angle );
}

Clock::~Clock()
{
	ClearDraw();
}

void Clock::Update()
{
	ClearDraw();
	CheckWallCollision();

	// Move in the current direction
	m_Pos = m_Pos + m_Dir * m_Speed;

	int hour, min, sec;
	GetTime( hour, min, sec );

	// Update draw
	DrawSquare();
	DrawHand(hour, TimeType::hour);
	DrawHand(min , TimeType::min);
	DrawHand(sec , TimeType::sec);
}

void Clock::ClearDraw()
{
	int d = m_Radius * 2;
	FillRect(m_Pos.x - m_Radius, m_Pos.y - m_Radius, d+1, d+1, GetRGB(0, 0, 0));
}

void Clock::DrawSquare()
{
	int d = m_Radius * 2;	
	DrawLine(m_Pos.x - m_Radius, m_Pos.y - m_Radius, m_Pos.x + m_Radius, m_Pos.y - m_Radius, GetRGB( 255, 255, 255 )); // Top
	DrawLine(m_Pos.x + m_Radius, m_Pos.y - m_Radius, m_Pos.x + m_Radius, m_Pos.y + m_Radius, GetRGB( 255, 255, 255 )); // Right
	DrawLine(m_Pos.x - m_Radius, m_Pos.y + m_Radius, m_Pos.x + m_Radius, m_Pos.y + m_Radius, GetRGB( 255, 255, 255 )); // Bottom
	DrawLine(m_Pos.x - m_Radius, m_Pos.y - m_Radius, m_Pos.x - m_Radius, m_Pos.y + m_Radius, GetRGB( 255, 255, 255 )); // Left
}

void Clock::DrawHand(int time, TimeType type)
{
	Vector2 v_hand;
	unsigned int color;
	float length = m_Radius;
	float denom;
	float angle;

	CustomizeHands(type, length, denom, color);

	// Hours are in 24-hour format, convert to 12-hour
	if(type == TimeType::hour) time %= 12;

	// Using the current time, find the angle of the hand in radians
	angle = time * (360.0f / denom);
	angle = angle * k_PI / 180.0f;

	// Set vector for clock hand using angle and length
	v_hand.x = sin( angle );
	v_hand.y = -cos( angle );
	v_hand = m_Pos + v_hand * length;

	DrawLine(m_Pos.x, m_Pos.y, v_hand.x, v_hand.y, color);
}

// Use TimeType to determine hand length, denominator, and color
// Note: Color not necessary, but makes hands more readable
void Clock::CustomizeHands(TimeType type, float &length, float &denom, unsigned int &color)
{
	switch(type){
	case TimeType::hour:
		length *= 0.5f;
		denom = 12;
		color = GetRGB(255, 100, 0);
		break;
	case TimeType::min:
		length *= 0.7f;
		denom = 60;
		color = GetRGB(0, 255, 255);
		break;
	case TimeType::sec:
		length *= 0.9f;
		denom = 60;
		color = GetRGB(100, 100, 255);
		break;
	}
}

void Clock::CheckWallCollision()
{
	// If colliding with wall, reverse direction
	if ((m_Pos.x - m_Radius < 0) || (m_Pos.x + m_Radius > m_ScreenWidth) )
	{
		m_Dir.x *= -1;
	}
	else if((m_Pos.y - m_Radius < 0) || (m_Pos.y + m_Radius > m_ScreenHeight))
	{
		m_Dir.y *= -1;
	}
}

bool Clock::CheckHitCollision(Vector2 head, Vector2 tail)
{
	// Line Segment-AABB Intersection Test
	Vector2 v_dir = tail - head;
	Vector2 v_invDir = Vector2( 1.0f / v_dir.x, 1.0f / v_dir.y );
	Vector2 v_boxMin = Vector2( m_Pos.x - m_Radius, m_Pos.y - m_Radius );
	Vector2 v_boxMax = Vector2( m_Pos.x + m_Radius, m_Pos.y + m_Radius );
	float tMin = 0.0f;
	float tMax = v_dir.Length();
	float txMin, txMax, tyMin, tyMax;

	v_dir.Normalize();

	txMin = (v_boxMin.x - tail.x) * v_invDir.x;
	txMax = (v_boxMax.x - tail.x) * v_invDir.x;

	if ( txMax < txMin ) std::swap( txMin, txMax );

	tMin = max( tMin, txMin );
	tMax = min( tMax, txMax );

	if(tMin > tMax) return false;

	tyMin = (v_boxMin.y - tail.y) * v_invDir.y;
	tyMax = (v_boxMax.y - tail.y) * v_invDir.y;

	if(tyMax < tyMin) std::swap(tyMin, tyMax);

	tMin = max(tMin, tyMin);
	tMax = min(tMax, tyMax);

	if(tMin > tMax) return false;

	// Clock has been hit by projectile
	if (m_Radius == LG_RADIUS)
	{
		ClearDraw();
		m_Radius = SM_RADIUS;

		// Head in a new direction
		int angle = std::rand() % 360;
		m_Dir.x = sin( angle );
		m_Dir.y = -cos( angle );
	}
	else
	{
		m_isAlive = false;
	}
	return true;
}