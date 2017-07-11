#include "Clock.h"
#include "graphics.h"
#include "time.h"
#include <cstdlib> // for rand
#include <utility> // for swap

#define MAX_RADIUS 50
#define MAX_CLOCK_LIFE 5

static const float k_PI = 3.1415926536f;

Clock::Clock(int screenWidth, int screenHeight, int livesLeft)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
	, m_Lives(livesLeft)
{
	// Determine radius based on lives remaining
	m_Radius = (m_Lives == MAX_CLOCK_LIFE) ? MAX_RADIUS : MAX_RADIUS / (2 * (5 - m_Lives));

	// Pick a random speed and direction
	m_Speed = rand() % 4 + 2;

	int angle = rand() % 360;
	m_Dir.x = sin(angle);
	m_Dir.y = -cos(angle);
}

Clock::~Clock(){}

void Clock::Update()
{
	ClearDraw();
	CheckWallCollision();

	// Move in the current direction
	m_Pos = m_Pos + m_Dir * m_Speed;

	int hour, min, sec;
	GetTime(hour, min, sec);

	// Update draw
	DrawSquare();
	DrawHand(hour, TimeType::hour);
	DrawHand(min , TimeType::min);
	DrawHand(sec , TimeType::sec);
}

void Clock::FindNewSpawnPosition(Vector2 prevPos)
{
	bool spawnInsidePrev = (m_Lives < MAX_CLOCK_LIFE);

	if(spawnInsidePrev)
	{
		// Finds a random spawn within the area of the previous clock
		float prevRadius = m_Radius * 2 + 10; 
		m_Pos.x = RandomFromRange(max(0, prevPos.x - prevRadius), min(m_ScreenWidth - prevRadius, prevPos.x + prevRadius));
		m_Pos.y = RandomFromRange(max(0, prevPos.y - prevRadius), min(m_ScreenHeight - prevRadius, prevPos.y + prevRadius));
	}
	else
	{
		// Finds a random spawn within screen bounds 
		m_Pos.x = rand() % (int)(m_ScreenWidth  - m_Radius*2) + m_Radius;
		m_Pos.y = rand() % (int)(m_ScreenHeight - m_Radius*2) + m_Radius;
	}
}

void Clock::ClearDraw()
{
	int d = m_Radius * 2;
	FillRect(m_Pos.x-m_Radius-2, m_Pos.y-m_Radius-2, d+4, d+4, GetRGB(0, 0, 0));
}

void Clock::DrawSquare()
{
	int d = m_Radius * 2;	
	DrawLine(m_Pos.x - m_Radius, m_Pos.y - m_Radius, m_Pos.x + m_Radius, m_Pos.y - m_Radius, GetRGB( 255, 0, 0 )); // Top
	DrawLine(m_Pos.x + m_Radius, m_Pos.y - m_Radius, m_Pos.x + m_Radius, m_Pos.y + m_Radius, GetRGB( 255, 0, 0 )); // Right
	DrawLine(m_Pos.x - m_Radius, m_Pos.y + m_Radius, m_Pos.x + m_Radius, m_Pos.y + m_Radius, GetRGB( 255, 0, 0 )); // Bottom
	DrawLine(m_Pos.x - m_Radius, m_Pos.y - m_Radius, m_Pos.x - m_Radius, m_Pos.y + m_Radius, GetRGB( 255, 0, 0 )); // Left
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
	v_hand.x = sin(angle);
	v_hand.y = -cos(angle);
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

void Clock::ReverseDirection()
{
	m_Dir.x *= -1;
	m_Dir.y *= -1;
}

// Vector Reflection
void Clock::CheckWallCollision()
{	
	// Order: Top Left, Top Right, Bottom Left, Bottom Right
	Vector2 v_screenTL = Vector2(0, 0);
	Vector2 v_screenTR = Vector2(m_ScreenWidth, 0);
	Vector2 v_screenBL = Vector2(0, m_ScreenHeight);
	Vector2 v_screenBR = Vector2(m_ScreenWidth, m_ScreenHeight);

	Vector2 v_wall, v_wallNormal;
	
	if(m_Pos.x - m_Radius < 0) 
	{
		// Left wall
		v_wall = v_screenTL - v_screenBL;
		v_wall.Normalize();
		v_wallNormal = Vector2(-v_wall.y, v_wall.x);
	}
	else if(m_Pos.x + m_Radius > m_ScreenWidth)	
	{
		// Right wall
		v_wall = v_screenTR - v_screenBR;
		v_wall.Normalize();
		v_wallNormal = Vector2(-v_wall.y, v_wall.x);
	}
	else if(m_Pos.y - m_Radius < 0)
	{
		// Top wall
		v_wall = v_screenTL - v_screenTR;
		v_wall.Normalize();
		v_wallNormal = Vector2(-v_wall.y, v_wall.x);

	}
	else if(m_Pos.y + m_Radius > m_ScreenHeight)
	{
		// Bottom wall
		v_wall = v_screenBL - v_screenBR;
		v_wall.Normalize();
		v_wallNormal = Vector2(-v_wall.y, v_wall.x);
	}

	m_Dir = m_Dir - (v_wallNormal * 2) * m_Dir.Dot(v_wallNormal);
	m_Dir.Normalize();
}

// AABB Collision Test
bool Clock::CheckClockCollision(Vector2 bPos, float bRadius)
{
	Vector2	v_minA = Vector2(m_Pos.x - m_Radius, m_Pos.y - m_Radius);
	Vector2	v_maxA = Vector2(m_Pos.x + m_Radius, m_Pos.y + m_Radius);
	Vector2 v_minB = Vector2(bPos.x - bRadius, bPos.y - bRadius);
	Vector2 v_maxB = Vector2(bPos.x + bRadius, bPos.y + bRadius);
	bool noCollide = ( v_minA.x > v_maxB.x || v_minB.x > v_maxA.x
					|| v_minA.y > v_maxB.y || v_minB.y > v_maxA.y );
	return !noCollide;
}

// Line Segment-AABB Intersection Test
bool Clock::CheckHitCollision(Vector2 head, Vector2 tail)
{
	Vector2 v_dir = tail - head;
	Vector2 v_invDir = Vector2(1.0f / v_dir.x, 1.0f / v_dir.y);
	Vector2 v_boxMin = Vector2(m_Pos.x - m_Radius, m_Pos.y - m_Radius);
	Vector2 v_boxMax = Vector2(m_Pos.x + m_Radius, m_Pos.y + m_Radius);
	float tMin = 0.0f;
	float tMax = v_dir.Length();
	float txMin, txMax, tyMin, tyMax;

	v_dir.Normalize();

	txMin = (v_boxMin.x - tail.x) * v_invDir.x;
	txMax = (v_boxMax.x - tail.x) * v_invDir.x;

	if (txMax < txMin) std::swap(txMin, txMax);

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
	m_Lives--;
	ClearDraw();
	return true;
}

// Helper function for FindNewSpawnPosition
// Returns float between a and b
float Clock::RandomFromRange(float a, float b)
{
	float randomPos = (float) rand() / RAND_MAX;  // 0.0 to 1.0
	randomPos *= (b - a);
	return a + randomPos;
}